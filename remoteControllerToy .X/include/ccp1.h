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
#ifndef CCP1_H
#define	CCP1_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define CCP1_MODE 0x02 // 0:Capture, 1:Compare, 2:PWM

#define CCP1M_DISABLE (uint8_t)0x00
#define CCP1M_CAPTRE_EVERY_FALLING (uint8_t)0x04
#define CCP1M_CAPTURE_EVERY_RISING (uint8_t)0x05
#define CCP1M_CAPTURE_EVERY_4TH_RISING (uint8_t)0x06
#define CCP1M_CAPTURE_EVERY_16TH_RISING (uint8_t)0x07
#define CCP1M_COMPARE_SET_OUTPUT_ON_MATCH (uint8_t)0x08
#define CCP1M_COMPARE_CLEAR_OUTPUT_ON_MATCH (uint8_t)0x09
#define CCP1M_CPMARE_GEN_SOFT_INTERRUPT_ON_MATCH (uint8_t)0x0A
#define CCP1M_TRIGGEER_SPECIAL_EVENT (uint8_t)0x0B
#define CCP1M_PWM (uint8_t)0x0C

#define GetCCP1CaptureValue() (uint16_t)((CCPR1H << 8) | CCPR1L)

void CCP1Initialize(void);

#if CCP1_MODE == 0x00
    
#elif CCP1_MODE == 0x01
    
#elif CCP1_MODE == 0x02
void CCP1PWMSetDuty(uint16_t);
uint16_t CCP1PWMGetDuty(void);
void CCP1PWMStart(void);
void CCP1PWMStop(void);
void CCP1PWMRestart(void);
void CCP1PWMPause(void);
#endif

#endif	/* XC_HEADER_TEMPLATE_H */

