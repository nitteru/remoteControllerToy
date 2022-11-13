/*
 * File:   ccp1.c
 * Author: Teruyuki
 *
 * Created on 2022/07/27, 12:40
 */


#include <xc.h>
#include "ccp1.h"

void CCP1Initialize(void) {
#if CCP1_MODE == 0x00
    //CCPR1L = 0x00;
    //CCPR1H = 0x00;    
#elif CCP1_MODE == 0x01
    
#elif CCP1_MODE == 0x02
    /*
     * PWMモード時はTMR2を使います
     * TMR2の設定は別途行ってください
     * 
     * 別途出力先GPIOの出力設定も必要です
     */
    CCP1CONbits.CCP1M = CCP1M_PWM; // PWM mode
    
    CCPR1L = 0x00;
    CCPR1H = 0x00;
#endif
}

#if CCP1_MODE == 0x02
void CCP1PWMSetDuty(uint16_t value)
{
    value = value & 0x03FF;
    CCP1CONbits.CCP1X = (uint8_t)((value >> 1) & 0x01);
    CCP1CONbits.CCP1Y = (uint8_t)(value & 0x01);
    CCPR1L = (uint8_t)(value << 2);
}

void CCP1PWMStart(void)
{
    CCPR1L = 0x00;
    CCPR1H = 0x00;
    
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
}

void CCP1PWMStop(void)
{
    CCP1CONbits.CCP1X = 0;
    CCP1CONbits.CCP1Y = 0;
    CCP1CONbits.CCP1M = 0x00; // Module OFF, 出力状態を維持したい場合は不要?
    CCPR1L = 0x00;
    CCPR1H = 0x00;
    
    T2CONbits.TMR2ON = 0;
    TMR2 = 0x00;
}

void CCP1PWMRestart(void)
{
    T2CONbits.TMR2ON = 1;
    CCP1CONbits.CCP1M = 0x06; // PWM mode
}

void CCP1PWMPause(void)
{
    T2CONbits.TMR2ON = 0;
    CCP1CONbits.CCP1M = 0x00; // 出力状態を維持したい場合は不要?
}
#endif