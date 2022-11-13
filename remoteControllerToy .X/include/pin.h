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
#pragma once

#include <xc.h> // include processor files - each processor file is guarded.  


//#define INPUT_RA0 PORTAbits.RA0

// ステータスLED1
#define LED1_SetHigh() \
    do                      \
    {                       \
        PORTDbits.RD2 = 1; \
    } while (0)
#define LED1_SetLow()  \
    do                      \
    {                       \
        PORTDbits.RD2 = 0; \
    } while (0)
#define LED1_Toggle()                \
    do                                    \
    {                                     \
        PORTDbits.RD2 = ~PORTDbits.RD2; \
    } while (0)
#define LED1_getValue() PORTBbits.RD2
#define LED1_SetDigitalInput() \
    do                              \
    {                               \
        TRISBbits.TRISD2 = 1;       \
    } while (0)
#define LED1_SetDigitalOutput() \
    do                               \
    {                                \
        TRISBbits.TRISD2 = 0;        \
    } while (0)
#define LED1_SetPullup() \
    do                        \
    {                         \
        WPUBbits.WPUD2 = 1;   \
    } while (0)
#define LED1_ResetPullup() \
    do                          \
    {                           \
        WPUBbits.WPUD2 = 0;     \
    } while (0)
#define LED1_SetAnalogMode() \
    do                            \
    {                             \
        ANSELBbits.ANSD2 = 1;     \
    } while (0)
#define LED1_SetDigitalMode() \
    do                             \
    {                              \
        ANSELBbits.ANSD2 = 0;      \
    } while (0)

#if 1
// デバッグ RB6, TP5
#define DEBUG_SetHigh() \
    do                      \
    {                       \
        PORTDbits.RD2 = 1; \
    } while (0)
#define DEBUG_SetLow()  \
    do                      \
    {                       \
        PORTDbits.RD2 = 0; \
    } while (0)
#define DEBUG_Toggle()                \
    do                                    \
    {                                     \
        PORTDbits.RD2 = ~PORTDbits.RD2; \
    } while (0)
#define DEBUG_getValue() PORTBbits.RD2
#define DEBUG_SetDigitalInput() \
    do                              \
    {                               \
        TRISBbits.TRISD2 = 1;       \
    } while (0)
#define DEBUG_SetDigitalOutput() \
    do                               \
    {                                \
        TRISBbits.TRISD2 = 0;        \
    } while (0)
#define DEBUG_SetPullup() \
    do                        \
    {                         \
        WPUBbits.WPUD2 = 1;   \
    } while (0)
#define DEBUG_ResetPullup() \
    do                          \
    {                           \
        WPUBbits.WPUD2 = 0;     \
    } while (0)
#define DEBUG_SetAnalogMode() \
    do                            \
    {                             \
        ANSELBbits.ANSD2 = 1;     \
    } while (0)
#define DEBUG_SetDigitalMode() \
    do                             \
    {                              \
        ANSELBbits.ANSD2 = 0;      \
    } while (0)
#endif

void PinInitialize(void);
