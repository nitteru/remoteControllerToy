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
    CCP2CONbits.CCP2M = 0x04; // 0x04:Every falling edge, 0x05:Every rising edge, 0x06:Every 4th rising edge, 0x07:Every 16th rising edge
    
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

    CCP2CONbits.CCP2M = 0x06; // PWM mode
    
    CCPR2L = 0x00;
    CCPR2H = 0x00;
#endif
}
