/*
 * File:   interrupt.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 1:06 PM
 */


#include <xc.h>
#include "interrupt.h"
#include "main.h"
#include "tmr0.h"
#include "tmr1.h"
#include "pin.h"

void __interrupt() interruptHandler(void)
{
    // interrupt handler
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        // TMR0
        INTCONbits.TMR0IF = 0;
        TMR0 = RELOAD_TMR0;
        intvTmrFlg.fields.flag10msec = 1;
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
            // TMR1 (Capture)
            PIR1bits.TMR1IF = 0;
            T1CONbits.TMR1ON = 0;
            TMR1H = RELOAD_TMR1_H;
            TMR1L = RELOAD_TMR1_L;
            T1CONbits.TMR1ON = 1;
            
             // オーバーフローフラグ
            captureTimerOverflow = 1;
        }
        else if(PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
        {
            // TMR2 (PWM)
            PIR1bits.TMR2IF = 0;
            /*
             * 1周期出力したらRGBの順で電源供給を切り替える
             * 15.625kHzを3回で192usec(5.2089kHz)で1周
             * 
             * 割り込みが間に合わず色が交じるので他の方法を検討する
             * PWM調光しなければインターバルタイマーで切り替えられる
             */
            if(ledColorSts == LED_R)
            {
                PORTD = 0b01100000;
                
                // 次回割り込み時に更新するため準備しておく
                pwmDutyLED_G = pwmDutyLED_G & 0x03FF;
                CCP1CONbits.CCP1X = (uint8_t)((pwmDutyLED_G >> 1) & 0x01);
                CCP1CONbits.CCP1Y = (uint8_t)(pwmDutyLED_G & 0x01);
                CCPR1L = (uint8_t)(pwmDutyLED_G >> 2);
                
                ledColorSts = LED_G;
            }
            else if(ledColorSts == LED_G)
            {
                PORTD = 0b10100000;

                // 次回割り込み時に更新するため準備しておく
                pwmDutyLED_B = pwmDutyLED_B & 0x03FF;
                CCP1CONbits.CCP1X = (uint8_t)((pwmDutyLED_B >> 1) & 0x01);
                CCP1CONbits.CCP1Y = (uint8_t)(pwmDutyLED_B & 0x01);
                CCPR1L = (uint8_t)(pwmDutyLED_B >> 2);
                
                ledColorSts = LED_B;
            }
            else if(ledColorSts == LED_B)
            {
                PORTD = 0b11000000;
                
                // 次回割り込み時に更新するため準備しておく
                pwmDutyLED_R = pwmDutyLED_R & 0x03FF;
                CCP1CONbits.CCP1X = (uint8_t)((pwmDutyLED_R >> 1) & 0x01);
                CCP1CONbits.CCP1Y = (uint8_t)(pwmDutyLED_R & 0x01);
                CCPR1L = (uint8_t)(pwmDutyLED_R >> 2);

                ledColorSts = LED_R;
            }
        }
        else if(PIE2bits.EEIE == 1 && PIR2bits.EEIF == 1)
        {
            // EEPROM Write
            PIR2bits.EEIF = 0;
        }
        else if(PIE1bits.CCP1IE == 1 && PIR1bits.CCP1IF == 1)
        {
            // CCP1
            PIR1bits.CCP1IF = 0;
        }
        else if(PIE2bits.CCP2IE == 1 && PIR2bits.CCP2IF == 1)
        {
            // CCP2
            PIR2bits.CCP2IF = 0;
            
            // キャプチャしたタイマーの値を取得
            edgeCaptureValue = (uint16_t)(CCPR2H << 8) | (uint16_t)CCPR2L;
            isCaptured = 1;
            
            T1CONbits.TMR1ON = 0;
            TMR1H = RELOAD_TMR1_H;
            TMR1L = RELOAD_TMR1_L;
            T1CONbits.TMR1ON = 1;  
        }
    }
}
