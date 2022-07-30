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
    
#elif CCP2_MODE == 0x01
    
#elif CCP2_MODE == 0x02
    /*
     * PWMモード時はTMR1を使います
     * TMR1の設定は別途行ってください
     * 
     * 別途出力先GPIOの出力設定も必要です
     */
    CCP1CONbits.CCP1M = 0x06; // PWM mode
    
    CCPR1L = 0x00;
    CCPR1H = 0x00;
#endif
}
