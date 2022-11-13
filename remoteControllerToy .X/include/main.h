/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#pragma once

#include <xc.h> // include processor files - each processor file is guarded.  

/*
 * デバッグ用スイッチ
 */
#define DEBUG_PRINT // UART出力

// インターバルタイマ カウンタ上限値 10msec*上限値
#define INTERVALTIMER_100MSEC (uint8_t)10
#define INTERVALTIMER_200MSEC (uint8_t)20
#define INTERVALTIMER_500MSEC (uint8_t)50
#define INTERVALTIMER_1SEC (uint8_t)100
#define INTERVALTIMER_2SEC (uint8_t)200

#define DATA_BUFFER_SIZE (uint8_t)32 // 受信データバッファサイズ

#define RECEIVE_TIMEOUT_10MSEC (uint8_t)15 // 受信タイムアウト時間 * 10msec
#define AEHA_TRAILER_TIME (uint8_t)1 // AEHAフォーマット トレイラー時間(8msec以上) * 10msec

/*
 * 受信解析全般
 * 
 * 変調単位と各フィールドの誤差を含めた判定の方法
 * 16bitタイマー TMR1を使用
 * 各フィールド､ビットのtyp幅と誤差範囲を2次元配列に入れて判定
 * → フィールド固定のNECフォーマットには使えそう｡AEHAは可変長フレームなので最後の見つけ方を工夫する?
 * LSBから送信される
 */

/*
 * NECフォーマット解析用
 * 変調
 *   950nm, サブキャリア 38kHz typ 1/3duty
 * Frame
 *   Leader, Customer Code (8bit), Customer Code INV (8bit), Data (8bit), Data INV (8bit), Stop bit (1T)
 * Repeat
 *   16T On, 4T Off, Stop bit (1T)
 * Transmission
 *   FrameとRepeat間は108msec
 * 
 * 変調単位の±30%を読み取る 0.392～0.728msec (±168usec) → TMR1分解能 2usec前後?, 16bitタイマーで125msec前後まで測定可能
 */
#if 0
#define NEC_MODULATE_UNIT_T 562 // 変調単位(usec) → タイマー分解能で割る, 下のTもタイマー分解能*値にする
#define NEC_MODULATE_UNIT_T (uint16_t)280 // 変調単位(usec, TMR1 2usec * Values)
#define NEC_FRAME_LEADER_ON 16T 
#define NEC_FRAME_LEADER_OFF 8T 
#define NEC_FRAME_LEADER_TOTAL 24T // 最長パルス幅 13.488msec
#define NEC_DATA_ZERO_ON 1T
#define NEC_DATA_ZERO_OFF 1T
#define NEC_DATA_ZERO_TOTAL 2T
#define NEC_DATA_ONE_ON 1T
#define NEC_DATA_ONE_OFF 3T
#define NEC_DATA_ONE_TOTAL 4T
#endif

/*
 * 家製協(AEHA)フォーマット解析用
 * 変調
 *   950nm, サブキャリア 38kHz typ 1/3duty 
 * Frame
 *   Leader, Customer Code (16bit), パリティ カスタマーコードを4bitずつXOR (4bit), Data0 (8bit), Data N (8bit), Stop bit (1T), Trailer
 *   N: 6 (48bit) typ
 *   Trailer 8msec以上の無送信区間?
 * Repeat
 *   8T On, 8T Off, Stop bit (1T)
 * Transmission
 *   FrameとRepeat間は130msec typ (規定はされていない)
 * 
 * 0.425msec±18%(±75usec)を範囲とする?
 */
#if 0
#define NEC_MODULATE_UNIT_T 425 // 変調単位 typ(usec) 350～500usec → タイマー分解能で割る, 下のTもタイマー分解能*値にする
#define NEC_FRAME_LEADER_ON 8T
#define NEC_FRAME_LEADER_OFF 4T 
#define NEC_FRAME_LEADER_TOTAL 12T // 最長パルス幅 5.1msec
#define NEC_DATA_ZERO_ON 1T
#define NEC_DATA_ZERO_OFF 1T
#define NEC_DATA_ZERO_TOTAL 2T
#define NEC_DATA_ONE_ON 1T
#define NEC_DATA_ONE_OFF 3T
#define NEC_DATA_ONE_TOTAL 4T
#endif

// インターバルタイマ カウンタ
typedef union
{
    uint8_t A[6];
    struct
    {
        // LSB
        uint8_t counter10msec;
        uint8_t counter100msec;
        uint8_t counter200msec;
        uint8_t counter500msec;
        uint8_t counter1sec;
        uint8_t counter2sec;
        // MSB
    } fields;
} intervalTimerCounters;


// インターバルタイマ フラグ
typedef union
{
    uint8_t A;
    struct
    {
        // LSB
        uint8_t flag10msec:1;
        uint8_t flag100msec:1;
        uint8_t flag200msec:1;
        uint8_t flag500msec:1;
        uint8_t flag1sec:1;
        uint8_t flag2sec:1;
        // MSB
    } fields;
} intervalTimerFlags;

enum nodeFrame
{
    NODE_WAIT, // 受信待機
    // 以下､リーダーを見てフォーマットを判断
    NODE_NEC_CUSTOMERCODE_L, // カスタマーコード下位 (NEC)
    NODE_NEC_CUSTOMERCODE_H, // カスタマーコード上位 (NEC)
    NODE_NEC_DATA, // データ (NEC)
    NODE_NEC_nDATA, // 反転データ (NEC)
    NODE_NEC_REPEAT, // リピートコード (NEC)
    NODE_AEHA_CUSTOMERCODE_L, // カスタマーコード下位 (AEHA)
    NODE_AEHA_CUSTOMERCODE_H, // カスタマーコード上位 (AEHA)
    NODE_AEHA_PARITY_SYSTEM, // パリティ4ビット+システムコード4ビット (AEHA)
    NODE_AEHA_DATA_N, // データ 送信バイト数は任意
    NODE_TIMEOUT, // 受信タイムアウト
    NODE_RECEIVE_COMPLETE_NEC, // NECフォーマット受信完了
    NODE_RECEIVE_COMPLETE_AEHA, // AEHAフォーマット受信完了
            // AEHAはトレーラ(1T, 8ms以上の空白)をもって終端とする
            // NECは規定バイト数受信したら完了とする
    NODE_WAIT_FOR_REPEAT // リピート待ち → タイムアウトで終了
};

// 受信したデータ
enum receiveData
{
    NEC_LEADER, // NECフォーマットリーダー
    AEHA_LEADER, // AEHAフォーマットリーダー
};

extern intervalTimerFlags intvTmrFlg; // インターバルタイマフラグ
extern uint16_t edgeCaptureValue; // キャプチャした値
extern uint8_t isCaptured;
extern uint8_t captureTimerOverflow; // キャプチャタイマーOFフラグ

void calIntervalTimer(void);
