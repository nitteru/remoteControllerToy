/*
 * File:   init.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 11:26 AM
 */


#include <xc.h>
#include "init.h"
#include "interrupt.h"
#include "pin.h"
#include "tmr0.h"
#include "tmr1.h"
#include "tmr2.h"
#include "usart.h"
#include "eeprom.h"

void systemInitialize(void) {
    //OSCInitialize(); Config設定(外付けXtal)のみ
    WDTInitialize();
    PinInitialize();
    TMR0Initialize();
    TMR1Initialize();
    TMR2Initialize();
    USARTInitialize();
    EEPROMInitialize();
}

/*
void OSCInitialize(void)
{
    
}
*/

void WDTInitialize(void)
{
    // Watchdog Timer Time-out Period: min 7msec, typ 18msec, max 33msec
    OPTION_REGbits.PS = 0x00;
    OPTION_REGbits.PSA = 0x00; // 8ビットプリスケーラはTMR0に割り当て
}