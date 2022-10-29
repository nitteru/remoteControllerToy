/*
 * File:   usart.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 2:56 PM
 */


#include <xc.h>
#include "usart.h"

void USARTInitialize(void) {
    PIE1bits.TXIE = 0;
    PIR1bits.TXIF = 0;
    PIE1bits.RCIE = 0;
    PIR1bits.RCIF = 0;
    
    SPBRG = SPBRG_VALUE;
    
    TXSTA = 0x00;
    RCSTA = 0x00;
    TXSTA = (uint8_t)(USART_CSRC_SLAVE | USART_TX9_DISABLE | USART_TXEN_ENABLE | USART_SYNC_DISABLE | USART_BRGH_HIGH);
    RCSTA = (uint8_t)(USART_SPEN_EBABLE | USART_RX9_DISABLE | USART_SREN_DISABLE | USART_CREN_ENABLE | USART_ADDRN_DISABLE);
    
    PIE1bits.RCIE = 1;
}

void USART_Write(uint8_t data)
{
    while (0 == PIR1bits.TXIF)
    {
    }

    TXREG = data;
}