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

#define TMR2_TOUTPS_1_16 (uint8_t)0x78
#define TMR2_TOUTPS_1_15 (uint8_t)0x70
#define TMR2_TOUTPS_1_14 (uint8_t)0x68
#define TMR2_TOUTPS_1_13 (uint8_t)0x60
#define TMR2_TOUTPS_1_12 (uint8_t)0x58
#define TMR2_TOUTPS_1_11 (uint8_t)0x50
#define TMR2_TOUTPS_1_10 (uint8_t)0x48
#define TMR2_TOUTPS_1_9 (uint8_t)0x40
#define TMR2_TOUTPS_1_8 (uint8_t)0x38
#define TMR2_TOUTPS_1_7 (uint8_t)0x30
#define TMR2_TOUTPS_1_6 (uint8_t)0x28
#define TMR2_TOUTPS_1_5 (uint8_t)0x20
#define TMR2_TOUTPS_1_4 (uint8_t)0x18
#define TMR2_TOUTPS_1_3 (uint8_t)0x10
#define TMR2_TOUTPS_1_2 (uint8_t)0x08
#define TMR2_TOUTPS_1_1 (uint8_t)0x00
#define TMR2_TMR2ON_ON (uint8_t)0x04
#define TMR2_TMR2ON_OFF (uint8_t)0x00
#define TMR2_T2CKPS_1 (uint8_t)0x00
#define TMR2_T2CKPS_4 (uint8_t)0x01
#define TMR2_T2CKPS_16 (uint8_t)0x02

#define RELOAD_TMR2 (uint8_t)0x00
#define RELOAD_PR2 (uint8_t)0xFF

#define TMR2InterruptEnable() (PIE1bits.TMR2IE = 0x01)
#define TMR2InterruptDisable() (PIE1bits.TMR2IE = 0x00)
#define TMR2InterruptFlagClear() (PIR1bits.TMR2IF = 0x00)

void TMR2Initialize(void);
void TMR2Start(void);
void TMR2Stop(void);

