/*
 * File:   ccp1.c
 * Author: Teruyuki
 *
 * Created on 2022/07/27, 12:40
 */


#include <xc.h>
#include "ccp1.h"

void CCP1_Initialize(void) {
#if CCP1_MODE == 0x00
    
#elif CCP1_MODE == 0x01
    
#elif CCP1_MODE == 0x02
    /*
     * PWMモード時はTMR2を使います
     * TMR2の設定は別途行ってください
     * 
     * 別途出力先GPIOの出力設定も必要です
     */
    CCP1CONbits.CCP1M = 0x06; // PWM mode
    
    CCPR1L = 0x00;
    CCPR1H = 0x00;
#endif
}

#if CCP1_MODE == 0x02
void CCP1_PWM_SetDuty(uint16_t value)
{
    value = value & 0x03FF;
    CCPR1L = (uint8_t)(value >> 8);
    CCPR1H = (uint8_t)(value & 0xFF);
}

void CCP1_PWM_Start(void)
{
    CCPR1L = 0x00;
    CCPR1H = 0x00;
    
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
}

void CCP1_PWM_Stop(void)
{
    CCP1CONbits.CCP1M = 0x00; // Module OFF, 出力状態を維持したい場合は不要?
    CCPR1L = 0x00;
    CCPR1H = 0x00;
    
    T2CONbits.TMR2ON = 0;
    TMR2 = 0x00;
}

void CCP1_PWM_Restart(void)
{
    T2CONbits.TMR2ON = 1;
    CCP1CONbits.CCP1M = 0x06; // PWM mode
}

void CCP1_PWM_Pause(void)
{
    T2CONbits.TMR2ON = 0;
    CCP1CONbits.CCP1M = 0x00; // 出力状態を維持したい場合は不要?
}
#endif