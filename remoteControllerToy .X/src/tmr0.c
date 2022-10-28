/*
 * File:   tmr0.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 12:57 PM
 */


#include <xc.h>
#include "tmr0.h"

void TMR0Initialize(void) {
    uint8_t ret = 0;
    
    INTCONbits.TMR0IE = 0;
    INTCONbits.TMR0IF = 0;
    
    // プリスケーラー割り当てを変更する場合はWDTでOPRION_REGを編集すること
    // タイマーモード設定
    /*
    ret = OPTION_REG;
    ret |= (T0CS_INTERNAL_INSTRUCTION_CYCLE_CLOCK | T0SE_INCREMENT_HIGH_TO_LOW_T0CKI | TMR0_PS_1_256);
    OPTION_REG = ret;
    */
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 1;
    OPTION_REGbits.PS = 0x03;
    /*
     * Interval (256 - RELOAD_TMR0) * (FOSC / 4)^-1 * prescaler sec
     * exp. 16MHz, プリスケーラ 1:256, REALOD_TMR0 0x00
     *   256 * 200nsec * 256 = 16.384msec
     */
    TMR0 = RELOAD_TMR0;
    
    INTCONbits.TMR0IE = 1;
}
