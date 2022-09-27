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
     *   65535 * 250nsec * 8 = 131.07msec
     * 250nsec * 8 = 2usec
     *   Fosc / 4 = 250nsec @ 16MHz
     */    
    T1CON = 0x00;
    T1CON = (TMR1_T1CKPS_1_8 | TMR1_TMR1ON_OFF | TMR1_TMR1CS_FOSC4 | TMR1_T1SYNC_ENABLE | TMR1_T1OSCEN_DISABLE );
    
    TMR1H = RELOAD_TMR1_H;
    TMR1L = RELOAD_TMR1_L;
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