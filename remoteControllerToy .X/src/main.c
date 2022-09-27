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

uint8_t dataFrameBuffer[32]; // データ格納用 AEHAを踏まえて最大32バイトとする 

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
const uint8_t tbl[8][2] = {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0}
};

void main(void)
{
    disableGlobalInterrupt();
    disablePeripheralInterrupt();
    
    systemInitialize();

    // 内部インターバルタイマ
    intvTmrFlg.A = 0; // フラグ初期化
    for(uint8_t i = 0; i < 6; i++)
    {
        intvTmrCnt.A[i] = 0; // カウンタ初期化
    }
    
    enableGlobalInterrupt();
    enablePeripheralInterrupt();
    
    while(1)
    {
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
        
        if(STATUSbits.nPD == 0)
        {
            // nPD: 電源ONまたはSLEEPの実行で0
            
            if(STATUSbits.nTO == 0)
            {
                // nTO: WDTタイムアウト発生で0 → WDTタイムアウトで復帰
                // 例えばカウンタを用意して一定期間後に処理をする､など
            }
            else
            {
                // その他の割り込み要因で復帰
            }
        }
#endif

        // Todo CCPの設定を追加したい
        
#ifdef ENABLE_USART
        if(RCSTAbits.OERR)
        {
            // オーバーランエラー
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
#endif
        
        // 本処理
        // インターバルタイマ処理
        if(intvTmrFlg.fields.flag10msec)
        {
            intvTmrFlg.fields.flag10msec = 0;
            calIntervalTimer();
        }

        if(intvTmrFlg.fields.flag100msec)
        {
            intvTmrFlg.fields.flag100msec = 0;
        }

        if(intvTmrFlg.fields.flag200msec)
        {
            intvTmrFlg.fields.flag200msec = 0;
        }

        if(intvTmrFlg.fields.flag500msec)
        {
            intvTmrFlg.fields.flag500msec = 0;
        }

        if(intvTmrFlg.fields.flag1sec)
        {
            intvTmrFlg.fields.flag1sec = 0;
        }

        if(intvTmrFlg.fields.flag2sec)
        {
            intvTmrFlg.fields.flag2sec = 0;
        }

        if(isCaptured)
        {
            // CCP Captureでパルス幅を検出した
            isCaptured = 0;
            
            if(captureTimerOverflow)
            {
                // 測定可能範囲を超えている
                captureTimerOverflow = 0;
            }
            else
            {
                // パルスを検出した
                /*
                 * パルス幅範囲のデータ構造
                 * 各部位のLowパルス幅(赤外線出力期間)の既定値､誤差範囲を持つ
                 * 
                 */
            }
        }
    }
    return;
}

void calIntervalTimer(void)
{
    // 対象単位時間ごとに実行する
    // 10msec用フラグはTMR0割り込みで立てる
    if(++intvTmrCnt.fields.counter100msec == INTERVALTIMER_100MSEC)
    {
        intvTmrCnt.fields.counter100msec = 0;
        intvTmrFlg.fields.flag100msec = 1;
    }

    if(++intvTmrCnt.fields.counter200msec == INTERVALTIMER_200MSEC)
    {
        intvTmrCnt.fields.counter200msec = 0;
        intvTmrFlg.fields.flag200msec = 1;
    }
    
    if(++intvTmrCnt.fields.counter500msec == INTERVALTIMER_500MSEC)
    {
        intvTmrCnt.fields.counter500msec = 0;
        intvTmrFlg.fields.flag500msec = 1;
    }
    
    if(++intvTmrCnt.fields.counter1sec == INTERVALTIMER_1SEC)
    {
        intvTmrCnt.fields.counter1sec = 0;
        intvTmrFlg.fields.flag1sec = 1;
    }

    if(++intvTmrCnt.fields.counter2sec == INTERVALTIMER_2SEC)
    {
        intvTmrCnt.fields.counter2sec = 0;
        intvTmrFlg.fields.flag2sec = 1;
    }
}
