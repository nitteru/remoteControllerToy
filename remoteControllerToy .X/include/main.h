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

