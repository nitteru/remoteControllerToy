/*
 * File:   tmr2.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 12:58 PM
 */


#include <xc.h>
#include "tmr2.h"

void TMR2Initialize(void) {
    PIE1bits.TMR2IE = 0;
    PIR1bits.TMR2IF = 0;
    
    /*
     * Interval (RELOAD_PR2 - RELOAD_TMR2) / (FOSC / 4) * prescaler * postscaler
     * exp.
     *   256 * 200nsec * 16 * 16 = 13.1072msec
     */  
    T2CON = (uint8_t)(TMR2_TOUTPS_1_16 | TMR2_TMR2ON_OFF | TMR2_T2CKPS_16);
    
    TMR2 = RELOAD_TMR2;
    PR2 = RELOAD_PR2;
}

void TMR2Start(void)
{
    PIE1bits.TMR2IE = 0;
    PIR1bits.TMR2IF = 0;
    
    uint8_t ret = 0x00;
    ret = T2CON;
    T2CON = (uint8_t)(ret | TMR2_TMR2ON_ON);
    
    PIE1bits.TMR2IE = 1;
}

void TMR2Stop(void)
{
    PIE1bits.TMR2IE = 0;
    PIR1bits.TMR2IF = 0;
    
    uint8_t ret = 0x00;
    ret = T2CON;
    T2CON = (uint8_t)(ret | TMR2_TMR2ON_OFF);
}

void TMR2Reset(void)
{
    
}