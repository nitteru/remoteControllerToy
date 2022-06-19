/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#define ENABLE_USART

//TX
#define USART_CSRC_MASTER 0x80
#define USART_CSRC_SLAVE 0x00
#define USART_TX9_ENABLE 0x40
#define USART_TX9_DISABLE 0x00
#define USART_TXEN_ENABLE 0x20
#define USART_TXEN_DISABLE 0x00
#define USART_SYNC_ENABLE 0x10
#define USART_SYNC_DISABLE 0x00
#define USART_BRGH_HIGH 0x04
#define USART_BRGH_LOW 0x00

// RX
#define USART_SPEN_EBABLE 0x80
#define USART_SPEN_DISABLE 0x00
#define USART_RX9_ENABLE 0x40
#define USART_RX9_DISABLE 0x00
#define USART_SREN_ENABLE 0x20
#define USART_SREN_DISABLE 0x00
#define USART_CREN_ENABLE 0x10
#define USART_CREN_DISABLE 0x00
#define USART_ADDRN_ENABLE 0x08
#define USART_ADDRN_DISABLE 0x00

/*
 * Baud Rate Formula (SPBRG: 0 to 255)
 * BRGH = 0 (Low)
 * Async: Baud Rate = Fosc / (64 * (SPBRG + 1))
 * Sync: Baud Rate = Fosc / (4 * (SPBRG + 1))
 * 
 * BRGH = 1 (High)
 * Async: Baud Rate = Fosc / (16 * (SPBRG + 1))
 * 
 * exp.
 *   Async, BRGH = 1
 *   9615bps = 20MHz / (16 * (129 + 1)), 0x81 = 129
 */
#define SPBRG_VALUE 0x81

void USARTInitialize(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* USART_H */