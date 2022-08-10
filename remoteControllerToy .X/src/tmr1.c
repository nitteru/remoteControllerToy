/*
 * File:   tmr1.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 12:57 PM
 */


#include <xc.h>
#include "tmr1.h"

void TMR1Initialize(void) {
    PIE1bits.TMR1IE = 0;
    PIR1bits.TMR1IF = 0;

    /*
     * Interval (65535 - ((RELOAD_TMR1_H << 8) | RELOAD_TMR1_L)) / (FOSC / 4) * prescaler
     * exp.
     *   65535 * 200nsec * 8 = 104.856msec
     *   Fosc / 4 = 200nsec @ 20MHz
     */    
    T1CON = 0x00;
    T1CON = (TMR1_T1CKPS_1_8 | TMR1_TMR1ON_OFF | TMR1_TMR1CS_FOSC4 | TMR1_T1SYNC_ENABLE | TMR1_T1OSCEN_DISABLE );
    
    TMR1H = RELOAD_TMR1_H;
    TMR1L = RELOAD_TMR1_L;
    
    /*
     * NECフォーマット概要
     * 変調単位T 562usec
     * データビット: 0:1T,1T 1:1T,3T
     * フレーム: リーダー 16T,8T
     *           カスタマーコード 16bit (8bit + 反転8bitの場合もある)
     *           データ 8bit + 反転8bit
     * 固定長フレーム: 32bit
     * リピート: 16T,4T フレームの後、ボタンを押している間108ms周期で送信
     */
}

void TMR1Start(void)
{
    PIE1bits.TMR1IE = 0;
    PIR1bits.TMR1IF = 0;
    
    uint8_t ret = 0x00;
    ret = T1CON;
    T1CON = (uint8_t)(ret | TMR1_TMR1ON_ON);
    
    PIE1bits.TMR1IE = 1;
}

void TMR1Stop(void)
{
    PIE1bits.TMR1IE = 0;
    PIR1bits.TMR1IF = 0;
    
    uint8_t ret = 0x00;
    ret = T1CON;
    T1CON = (uint8_t)(ret | TMR1_TMR1ON_OFF);
}

void TMR1Reset(void)
{
    TMR1H = RELOAD_TMR1_H;
    TMR1L = RELOAD_TMR1_L;
}