/*
 * File:   main.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 10:42 AM
 */


#include "DeviceConfig.h"
#include <xc.h>
#include "main.h"
#include "pin.h"
#include "interrupt.h"
#include "init.h"
#include "usart.h"
#include "eeprom.h"
#include "tmr0.h"
#include "tmr1.h"
#include "tmr2.h"
#include "ccp1.h"

intervalTimerCounters intvTmrCnt;
intervalTimerFlags intvTmrFlg;

enum nodeFrame nFrame = NODE_WAIT;

uint16_t edgeCaptureValue = 0; // キャプチャした値
uint8_t captureTimerOverflow = 0; // キャプチャタイマーOF回数
uint8_t isCaptured = 0; // キャプチャ完了フラグ

uint8_t rcvByteFlag = 0; // 1バイト受信完了フラグ
uint8_t rcvByteBuffer = 0; // 1バイト受信バッファ
uint8_t rcvShiftCounter = 0; // 1バイト受信バッファシフトカウンタ
uint8_t dataFrameBuffer[DATA_BUFFER_SIZE]; // データバッファ AEHAを踏まえて最大32バイトとする?
uint8_t dataFrameCounter = 0; // データバッファの格納位置
uint8_t repeatFlag = 0; // リピート信号受信

uint8_t rcvTimeOutEnable = 0; // 受信タイムアウト管理
uint8_t rcvTimeOutFlag = 0; // 受信タイムアウトフラグ
uint8_t rcvTimeOutCounter = RECEIVE_TIMEOUT_10MSEC; // 受信タイムアウトカウンタ * 10msec

uint8_t aehaTrailerEnable = 0; // AEHAトレーラー受信管理
uint8_t aehaTrailerFlag = 0; // AEHAトレーラー受信フラグ
uint8_t aehaTrailerCounter = AEHA_TRAILER_TIME; // AEHAトレーラー用カウンタ
/*
 * High→Lowで区切られる区間の既定値(タイマーカウント値)､誤差範囲(概ね±30%)のセット
 * [0][*]: NECフォーマットリーダー 24T
 * [1][*]: AEHAフォーマットリーダー 12T
 * [2][*]: NECフォーマット 0 2T
 * [3][*]: NECフォーマット 1 4T
 * [4][*]: AEHAフォーマット 0 2T
 * [5][*]: AEHフォーマット 1 4T
 * [6][*]: NECフォーマットリピート 20T
 * [7][*]: AEHAフォーマットリピート 16T
 * 
 * TMR1の分解能: 250nsec * 8 = 2usec
 * 各区間を2usecで割った値で定義していく
 */
const uint16_t tbl[8][2] = {
    {6744, 2032},
    {2550, 765},
    {562, 168},
    {1124, 337},
    {425, 127},
    {850, 255},
    {5620, 1686},
    {3400, 1020}
};

void main(void) {
    disableGlobalInterrupt();
    disablePeripheralInterrupt();

    systemInitialize();

    // 内部インターバルタイマ
    intvTmrFlg.A = 0; // フラグ初期化
    for (uint8_t i = 0; i < 6; i++) {
        intvTmrCnt.A[i] = 0; // カウンタ初期化
    }

    enableGlobalInterrupt();
    enablePeripheralInterrupt();

    while (1) {
        CLRWDT();
#if 0
        /*
         * SLEEPを使う場合
         * 1. 必要なら復帰に使わないペリフェラルのPIEを0にする
         *    (クロックが必要なペリフェラルを除く)
         * 2. 割り込みを行わない場合は事前にGIEを0にする
         * 3. SLEEPの次がプリフェッチされている｡実行したくない場合はNOPを置く｡
         * 4. WDTを確実にクリアするためにSLEEP直前にCLRWDTを置く
         */
        SLEEP();
        NOP();

        if (STATUSbits.nPD == 0) {
            // nPD: 電源ONまたはSLEEPの実行で0

            if (STATUSbits.nTO == 0) {
                // nTO: WDTタイムアウト発生で0 → WDTタイムアウトで復帰
                // 例えばカウンタを用意して一定期間後に処理をする､など
            } else {
                // その他の割り込み要因で復帰
            }
        }
#endif

        // Todo CCPの設定を追加したい

#ifdef ENABLE_USART
        if (RCSTAbits.OERR) {
            // オーバーランエラー
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
#endif

        // 本処理
        // インターバルタイマ処理
        if (intvTmrFlg.fields.flag10msec) {
            intvTmrFlg.fields.flag10msec = 0;
            calIntervalTimer();

            // 受信タイムアウトカウント
            if (rcvTimeOutEnable) {
                if (rcvTimeOutCounter-- == 0) {
                    // タイムアウト
                    rcvTimeOutCounter = RECEIVE_TIMEOUT_10MSEC;
                    rcvTimeOutEnable = 0;
                    //rcvTimeOutFlag = 1;
                    nFrame = NODE_TIMEOUT;
                }
            }

            if (aehaTrailerEnable) {
                /*
                 * AEHAトレーラーの確認
                 * AEHAフォーマットの場合､1ビット受信して8msec以上経過したらトレーラーとする
                 */
                if (aehaTrailerCounter-- == 0) {
                    aehaTrailerCounter = AEHA_TRAILER_TIME;
                    aehaTrailerEnable = 0;
                    aehaTrailerFlag = 1;
                    nFrame = NODE_RECEIVE_COMPLETE_AEHA;
                }
            }
        }

        if (intvTmrFlg.fields.flag100msec) {
            intvTmrFlg.fields.flag100msec = 0;
        }

        if (intvTmrFlg.fields.flag200msec) {
            intvTmrFlg.fields.flag200msec = 0;
        }

        if (intvTmrFlg.fields.flag500msec) {
            intvTmrFlg.fields.flag500msec = 0;
        }

        if (intvTmrFlg.fields.flag1sec) {
            intvTmrFlg.fields.flag1sec = 0;
        }

        if (intvTmrFlg.fields.flag2sec) {
            intvTmrFlg.fields.flag2sec = 0;
        }

        if (isCaptured) {
            // CCP Captureでパルス幅を検出した
            isCaptured = 0;

            // AEHAフォーマットのトレーラー検出フラグを立てる
            // 10msec以上経過したら受信完了
            // 通常のタイムアウト処理はいらないかも → リーダーを受信したら初期状態から開始になるため

            /*
             * パルス幅範囲のデータ構造
             * 各部位のLowパルス幅(赤外線出力期間)の既定値､誤差範囲を持つ
             * 
             */
            if (captureTimerOverflow) {
                nFrame = NODE_WAIT;
            } else {
                // どの区間に該当するか
                if (((tbl[0][0] - tbl[0][1]) < edgeCaptureValue) && (edgeCaptureValue < (tbl[0][0] + tbl[0][1]))) {
                    // NECフォーマットのリーダー
                    rcvTimeOutEnable = 1;
                    rcvTimeOutFlag = 0;
                    rcvTimeOutCounter = RECEIVE_TIMEOUT_10MSEC;

                    repeatFlag = 0;
                    rcvByteBuffer = 0;
                    rcvShiftCounter = 0;
                    rcvByteFlag = 0;
                    dataFrameCounter = 0;

                    for (uint8_t i = 0; i < DATA_BUFFER_SIZE; i++) {
                        dataFrameBuffer[i] = 0x00;
                    }

                    nFrame = NODE_NEC_CUSTOMERCODE_L;
                } else if (((tbl[1][0] - tbl[1][1]) < edgeCaptureValue) && (edgeCaptureValue < (tbl[1][0] + tbl[1][1]))) {
                    // AEHAフォーマットのリーダー
                    rcvTimeOutEnable = 1;
                    rcvTimeOutFlag = 0;
                    rcvTimeOutCounter = RECEIVE_TIMEOUT_10MSEC;

                    repeatFlag = 0;
                    rcvByteBuffer = 0;
                    rcvShiftCounter = 0;
                    rcvByteFlag = 0;
                    dataFrameCounter = 0;

                    for (uint8_t i = 0; i < DATA_BUFFER_SIZE; i++) {
                        dataFrameBuffer[i] = 0x00;
                    }

                    nFrame = NODE_AEHA_CUSTOMERCODE_L;
                } else if (((tbl[2][0] - tbl[2][1]) < edgeCaptureValue) && (edgeCaptureValue < (tbl[2][0] + tbl[2][1]))) {
                    // NEC,AEHAフォーマットの0
                    rcvByteBuffer = (rcvByteBuffer >> rcvShiftCounter);
                    if (++rcvShiftCounter == 8) {
                        // 1Byte受信
                        rcvByteFlag = 1;
                    }
                } else if (((tbl[3][0] - tbl[3][1]) < edgeCaptureValue) && (edgeCaptureValue < (tbl[3][0] + tbl[3][1]))) {
                    // NEC,AEHAフォーマットの1
                    rcvByteBuffer = (rcvByteBuffer >> rcvShiftCounter) & 0x80;
                    if (++rcvShiftCounter == 8) {
                        // 1Byte受信
                        rcvByteFlag = 1;
                    }
                } else if (((tbl[5][0] - tbl[5][1]) < edgeCaptureValue) && (edgeCaptureValue < (tbl[5][0] + tbl[5][1]))) {
                    // NECフォーマットのリピート
                    repeatFlag = 1;
                } else if (((tbl[6][0] - tbl[6][1]) < edgeCaptureValue) && (edgeCaptureValue < (tbl[6][0] + tbl[6][1]))) {
                    // AEHAフォーマットのリピート
                    repeatFlag = 1;
                }
            }
        }


        switch (nFrame) {
            case NODE_WAIT:
                // 受信待機
                break;
            case NODE_NEC_CUSTOMERCODE_L:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        dataFrameCounter = 0;
                        nFrame = NODE_WAIT;
                    }

                    nFrame = NODE_NEC_CUSTOMERCODE_H;
                }
                break;
            case NODE_NEC_CUSTOMERCODE_H:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        dataFrameCounter = 0;
                        nFrame = NODE_WAIT;
                    }

                    nFrame = NODE_NEC_DATA;
                }
                break;
            case NODE_NEC_DATA:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        dataFrameCounter = 0;
                        nFrame = NODE_WAIT;
                    }

                    nFrame = NODE_NEC_nDATA;
                }
                break;
            case NODE_NEC_nDATA:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        dataFrameCounter = 0;
                        nFrame = NODE_WAIT;
                    }

                    nFrame = NODE_RECEIVE_COMPLETE_NEC;
                }
                break;
            case NODE_AEHA_CUSTOMERCODE_L:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        dataFrameCounter = 0;
                        nFrame = NODE_WAIT;
                    }

                    nFrame = NODE_AEHA_CUSTOMERCODE_H;
                }
                break;
            case NODE_AEHA_CUSTOMERCODE_H:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        dataFrameCounter = 0;
                        nFrame = NODE_WAIT;
                    }

                    nFrame = NODE_AEHA_PARITY_SYSTEM;
                }
                break;
            case NODE_AEHA_PARITY_SYSTEM:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        dataFrameCounter = 0;
                        nFrame = NODE_WAIT;
                    }

                    aehaTrailerEnable = 1;
                    nFrame = NODE_AEHA_DATA_N;
                }
                break;
            case NODE_AEHA_DATA_N:
                if (rcvByteFlag) {
                    // 1バイト受信した
                    rcvByteFlag = 0;
                    dataFrameBuffer[dataFrameCounter] = rcvByteBuffer;

                    if (++dataFrameCounter == DATA_BUFFER_SIZE) {
                        //dataFrameCounter = 0;
                        nFrame = NODE_RECEIVE_COMPLETE_AEHA; // AEHAの場合は受信完了扱い
                    }
                    else {
                        nFrame = NODE_AEHA_DATA_N;
                        aehaTrailerCounter = AEHA_TRAILER_TIME;
                    }
                }
                break;
            case NODE_RECEIVE_COMPLETE_NEC:
                // ここでコマンドに応じた処理を行うか､処理部を外に出す
                // 受信バイト数: dataFrameCounter - 1
                // 受信内容: dataFrameBuffer[]
                
                // とりあえずUARTに出力
                
                nFrame = NODE_WAIT;
                break;
            case NODE_RECEIVE_COMPLETE_AEHA:
                // ここでコマンドに応じた処理を行うか､処理部を外に出す
                // 受信バイト数: dataFrameCounter - 1
                // 受信内容: dataFrameBuffer[]
                
                // とりあえずUARTに出力
                
                nFrame = NODE_WAIT;
                break;
            case NODE_TIMEOUT:
                // 受信タイムアウト
                // 受信した内容やカウンタをクリア → 内容はリピート信号で再利用するため
                nFrame = NODE_WAIT;
                break;
            case NODE_WAIT_FOR_REPEAT:
                // リピート信号待ち
                // 受信タイムアウトで終了
                break;
            default:
                break;
        }
    }
    return;
}

void calIntervalTimer(void) {
    // 対象単位時間ごとに実行する
    // 10msec用フラグはTMR0割り込みで立てる
    if (++intvTmrCnt.fields.counter100msec == INTERVALTIMER_100MSEC) {
        intvTmrCnt.fields.counter100msec = 0;
        intvTmrFlg.fields.flag100msec = 1;
    }

    if (++intvTmrCnt.fields.counter200msec == INTERVALTIMER_200MSEC) {
        intvTmrCnt.fields.counter200msec = 0;
        intvTmrFlg.fields.flag200msec = 1;
    }

    if (++intvTmrCnt.fields.counter500msec == INTERVALTIMER_500MSEC) {
        intvTmrCnt.fields.counter500msec = 0;
        intvTmrFlg.fields.flag500msec = 1;
    }

    if (++intvTmrCnt.fields.counter1sec == INTERVALTIMER_1SEC) {
        intvTmrCnt.fields.counter1sec = 0;
        intvTmrFlg.fields.flag1sec = 1;
    }

    if (++intvTmrCnt.fields.counter2sec == INTERVALTIMER_2SEC) {
        intvTmrCnt.fields.counter2sec = 0;
        intvTmrFlg.fields.flag2sec = 1;
    }
}
