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

// LED R
#define LED_R_SetHigh() \
    do                      \
    {                       \
        PORTDbits.RD7 = 1; \
    } while (0)
#define LED_R_SetLow()  \
    do                      \
    {                       \
        PORTDbits.RD7 = 0; \
    } while (0)
#define LED_R_Toggle()                \
    do                                    \
    {                                     \
        PORTDbits.RD7 = ~PORTDbits.RD7; \
    } while (0)
#define LED_R_getValue() PORTBbits.RD7
#define LED_R_SetDigitalInput() \
    do                              \
    {                               \
        TRISBbits.TRISD7 = 1;       \
    } while (0)
#define LED_R_SetDigitalOutput() \
    do                               \
    {                                \
        TRISBbits.TRISD7 = 0;        \
    } while (0)
#define LED_R_SetPullup() \
    do                        \
    {                         \
        WPUBbits.WPUD7 = 1;   \
    } while (0)
#define LED_R_ResetPullup() \
    do                          \
    {                           \
        WPUBbits.WPUD7 = 0;     \
    } while (0)
#define LED_R_SetAnalogMode() \
    do                            \
    {                             \
        ANSELBbits.ANSD7 = 1;     \
    } while (0)
#define LED_R_SetDigitalMode() \
    do                             \
    {                              \
        ANSELBbits.ANSD7 = 0;      \
    } while (0)

// LED G
#define LED_G_SetHigh() \
    do                      \
    {                       \
        PORTDbits.RD6 = 1; \
    } while (0)
#define LED_G_SetLow()  \
    do                      \
    {                       \
        PORTDbits.RD6 = 0; \
    } while (0)
#define LED_G_Toggle()                \
    do                                    \
    {                                     \
        PORTDbits.RD6 = ~PORTDbits.RD6; \
    } while (0)
#define LED_G_getValue() PORTBbits.RD6
#define LED_G_SetDigitalInput() \
    do                              \
    {                               \
        TRISBbits.TRISD6 = 1;       \
    } while (0)
#define LED_G_SetDigitalOutput() \
    do                               \
    {                                \
        TRISBbits.TRISD6 = 0;        \
    } while (0)
#define LED_G_SetPullup() \
    do                        \
    {                         \
        WPUBbits.WPUD6 = 1;   \
    } while (0)
#define LED_G_ResetPullup() \
    do                          \
    {                           \
        WPUBbits.WPUD6 = 0;     \
    } while (0)
#define LED_G_SetAnalogMode() \
    do                            \
    {                             \
        ANSELBbits.ANSD6 = 1;     \
    } while (0)
#define LED_G_SetDigitalMode() \
    do                             \
    {                              \
        ANSELBbits.ANSD6 = 0;      \
    } while (0)

// LED G
#define LED_B_SetHigh() \
    do                      \
    {                       \
        PORTDbits.RD5 = 1; \
    } while (0)
#define LED_B_SetLow()  \
    do                      \
    {                       \
        PORTDbits.RD5 = 0; \
    } while (0)
#define LED_B_Toggle()                \
    do                                    \
    {                                     \
        PORTDbits.RD5 = ~PORTDbits.RD5; \
    } while (0)
#define LED_B_getValue() PORTBbits.RD5
#define LED_B_SetDigitalInput() \
    do                              \
    {                               \
        TRISBbits.TRISD5 = 1;       \
    } while (0)
#define LED_B_SetDigitalOutput() \
    do                               \
    {                                \
        TRISBbits.TRISD5 = 0;        \
    } while (0)
#define LED_B_SetPullup() \
    do                        \
    {                         \
        WPUBbits.WPUD5 = 1;   \
    } while (0)
#define LED_B_ResetPullup() \
    do                          \
    {                           \
        WPUBbits.WPUD5 = 0;     \
    } while (0)
#define LED_B_SetAnalogMode() \
    do                            \
    {                             \
        ANSELBbits.ANSD5 = 1;     \
    } while (0)
#define LED_B_SetDigitalMode() \
    do                             \
    {                              \
        ANSELBbits.ANSD5 = 0;      \
    } while (0)

#if 1
// デバッグ RD2
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
