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
    /*
     * Captureモード時はTMR1を使います
     * TMR1の設定は別途行ってください
     * 
     * 別途出力先GPIOの出力設定も必要です
     */
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;
    CCPR2L = 0x00;
    CCPR2H = 0x00;
    CCP2CONbits.CCP2M = CCP2M_CAPTRE_EVERY_FALLING;
    
#elif CCP2_MODE == 0x01
    
#elif CCP2_MODE == 0x02
    /*
     * PWMモード時はTMR2を使います
     * TMR2の設定は別途行ってください
     * 
     * 別途出力先GPIOの出力設定も必要です
     */
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;

    CCP2CONbits.CCP2M = CCP2M_PWM; // PWM mode
    
    CCPR2L = 0x00;
    CCPR2H = 0x00;
#endif
    
    PIE2bits.CCP2IE = 1;
}

#if CCP2_MODE == 0x00
void CCP2CaptureStart(void)
{
    CCP2CONbits.CCP2M = CCP2M_CAPTRE_EVERY_FALLING;
}

void CCP2CaptureStop(void)
{
    CCP2CONbits.CCP2M = CCP2M_DISABLE; // プリスケーラもクリアされます
}
#elif CCP2MODE == 0x01
void CCP2SetCompareValue(uint16_t value)
{
    
}

#elif CCP2_MODE == 0x02
void CCP2PWMSetDuty(uint16_t value)
{
    value = value & 0x03FF;
    CCP2CONbits.CCP2X = (uint8_t)((value >> 1) & 0x01);
    CCP2CONbits.CCP2Y = (uint8_t)(value & 0x01);
    CCPR2L = (uint8_t)(value >> 8);
}

void CCP2PWMStart(void)
{
    CCP2CONbits.CCP2X = 0x01;
    CCP2CONbits.CCP2Y = 0x01;
    CCPR2L = 0xFF;
    TMR2 = 0;
    
    T2CONbits.TMR2ON = 1;
}

void CCP2PWMStop(void)
{
    T2CONbits.TMR2ON = 0;

    CCP2CONbits.CCP2X = 0x01;
    CCP2CONbits.CCP2Y = 0x01;
    //CCP2CONbits.CCP2M = CCP2M_DISABLE; // Module OFF, 出力状態を維持したい場合は不要?
    CCPR2L = 0xFF;
    
    TMR2 = 0x00;
}

void CCP2PWMRestart(void)
{
    CCP2CONbits.CCP2M = CCP2M_PWM; // PWM mode
    T2CONbits.TMR2ON = 1;
}

void CCP2PWMPause(void)
{
    T2CONbits.TMR2ON = 0;
    //CCP2CONbits.CCP2M = CCP2M_DISABLE; // 出力状態を維持したい場合は不要?
}
#endif