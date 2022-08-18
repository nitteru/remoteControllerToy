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
#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.  

// インターバルタイマ カウンタ上限値 10msec*上限値
#define INTERVALTIMER_100MSEC (uint8_t)10
#define INTERVALTIMER_200MSEC (uint8_t)20
#define INTERVALTIMER_500MSEC (uint8_t)50
#define INTERVALTIMER_1SEC (uint8_t)100
#define INTERVALTIMER_2SEC (uint8_t)200

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
 *   FrameとRepeat間は130msec typ
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

void calIntervalTimer(void);

#endif	/* MAIN_H */

