/*
 * File:   ccp2.c
 * Author: Teruyuki
 *
 * Created on July 30, 2022, 10:49 PM
 */


#include <xc.h>
#include "ccp2.h"

void CCP2Initialize(void)
{
#if CCP2_MODE == 0x00
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;
    CCP2CONbits.CCP2M = CCP2M_CAPTRE_EVERY_FALLING;
    
#elif CCP2_MODE == 0x01
    
#elif CCP2_MODE == 0x02
    /*
     * PWMモード時はTMR1を使います
     * TMR1の設定は別途行ってください
     * 
     * 別途出力先GPIOの出力設定も必要です
     */
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;

    CCP2CONbits.CCP2M = CCP2M_PWM; // PWM mode
    
    CCPR2L = 0x00;
    CCPR2H = 0x00;
#endif
}

#if CCP2_MODE == 0x00
void CCP2CaptureStart(void)
{
    
}

void CCP2CaptureStop(void)
{
    
}
#endif

#if CCP2_MODE == 0x02
void CCP2PWMSetDuty(uint16_t value)
{
    value = value & 0x03FF;
    CCPR1L = (uint8_t)(value >> 8);
    CCPR1H = (uint8_t)(value & 0xFF);
}

void CCP2PWMStart(void)
{
    CCPR1L = 0x00;
    CCPR1H = 0x00;
    
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
}

void CCP2PWMStop(void)
{
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;
    CCP2CONbits.CCP2M = 0x00; // Module OFF, 出力状態を維持したい場合は不要?
    CCPR1L = 0x00;
    CCPR1H = 0x00;
    
    T2CONbits.TMR2ON = 0;
    TMR2 = 0x00;
}

void CCP2PWMRestart(void)
{
    T2CONbits.TMR2ON = 1;
    CCP2CONbits.CCP2M = 0x06; // PWM mode
}

void CCP2PWMPause(void)
{
    T2CONbits.TMR2ON = 0;
    CCP2CONbits.CCP2M = 0x00; // 出力状態を維持したい場合は不要?
}
#endif