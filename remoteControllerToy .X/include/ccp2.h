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
#ifndef CCP2_H
#define	CCP2_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define CCP2_MODE 0 // 0:Capture, 1:Compare, 2:PWM

#define CCP2M_DISABLE (uint8_t)0x00
#define CCP2M_CAPTRE_EVERY_FALLING (uint8_t)0x04
#define CCP2M_CAPTURE_EVERY_RISING (uint8_t)0x05
#define CCP2M_CAPTURE_EVERY_4TH_RISING (uint8_t)0x06
#define CCP2M_CAPTURE_EVERY_16TH_RISING (uint8_t)0x07
#define CCP2M_COMPARE_SET_OUTPUT_ON_MATCH (uint8_t)0x08
#define CCP2M_COMPARE_CLEAR_OUTPUT_ON_MATCH (uint8_t)0x09
#define CCP2M_CPMARE_GEN_SOFT_INTERRUPT_ON_MATCH (uint8_t)0x0A
#define CCP2M_TRIGGEER_SPECIAL_EVENT (uint8_t)0x0B
#define CCP2M_PWM (uint8_t)0x0C

#define GetCCP2CaptureValue() ((uint16_t)(CCPR2H << 8) | (uint16_t)CCPR2L)


void CCP2Initialize(void);

#if CCP2_MODE == 0x00 // Capture
void CCP2CaptureStart(void);
void CCP2CaptureStop(void);
#elif CCP2_MODE == 0x01 // Compare
void CCP2SetCompareValue(uint16_t);
#elif CCP2_MODE == 0x02 // PWM
void CCP2PWMSetDuty(uint16_t);
uint16_t CCP2PWMGetDuty(void);
void CCP2PWMStart(void);
void CCP2PWMStop(void);
void CCP2PWMRestart(void);
void CCP2PWMPause(void);
#endif

#endif	/* XC_HEADER_TEMPLATE_H */

