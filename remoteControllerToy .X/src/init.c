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
#include "ccp1.h"
#include "ccp2.h"

void systemInitialize(void) {
    //OSCInitialize(); Config設定(外付けXtal)のみ
    WDTInitialize();
    PinInitialize();
    TMR0Initialize();
    TMR1Initialize();
    TMR2Initialize();
    USARTInitialize();
    EEPROMInitialize();
    CCP1Initialize();
    CCP2Initialize();
}

/*
void OSCInitialize(void)
{
    
}
*/

void WDTInitialize(void)
{
    // Watchdog Timer Time-out Period: min 7msec, typ 18msec, max 33msec
    //OPTION_REGbits.PS = 0x00;
    OPTION_REGbits.PSA = 0; // 8ビットプリスケーラはTMR0に割り当て
}