/*
 * File:   interrupt.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 1:06 PM
 */


#include <xc.h>
#include "interrupt.h"
#include "tmr0.h"
#include "tmr1.h"

void __interrupt() interruptHandler(void)
{
    // interrupt handler
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        // TMR0
        INTCONbits.TMR0IF = 0;
        TMR0 = RELOAD_TMR0;
    }
    else if(INTCONbits.INTE == 1 && INTCONbits.INTF == 1)
    {
        // EXT INT
        INTCONbits.INTF = 0;
    }
    else if(INTCONbits.PEIE == 1)
    {
        // Peripheral Interrupt
        if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1)
        {
            // USART Receive
            PIR1bits.RCIF = 0;
            
            if(RCSTAbits.OERR)
            {
                // オーバーランエラー
                RCSTAbits.CREN = 0;
                RCSTAbits.CREN = 1;
            }
            
            if(RCSTAbits.FERR)
            {
                // フレーミングエラー
                uint8_t ret = RCREG;
            }
        }
        else if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
        {
            // TMR1
            PIR1bits.TMR1IF = 0;
            T1CONbits.TMR1ON = 0;
            TMR1H = RELOAD_TMR1_H;
            TMR1L = RELOAD_TMR1_L;
            T1CONbits.TMR1ON = 1;
        }
        else if(PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
        {
            // TMR2
            /*
             * 1周期出力したらRGBの順で電源供給を切り替える
             * 19.53kHzを3回で154usec(6.51kHz)で1周
             */
        }
        else if(PIE2bits.EEIE == 1 && PIR2bits.EEIF == 1)
        {
            // EEPROM Write
            PIR2bits.EEIF = 0;
        }
    }
}
