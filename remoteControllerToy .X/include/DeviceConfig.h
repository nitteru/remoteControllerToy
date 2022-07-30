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
#ifndef DEVICE_CONFIG_H
#define	DEVICE_CONFIG_H

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

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#define _XTAL_FREQ 20000000

/*
 * {Install Drive}:/Program Files/Microchip/xc8/vx.xx/docs/chips/16f877.html
 */

/*
 * FOSC Oscillator Selection bits
 * EXTRC: RC oscillator, HS: HS oscillator, XT: XT oscillator, LP: LP oscillator
 */
#pragma config FOSC = HS

/*
 * WDTE Watchdog Timer Enable bit
 * ON: WDT enable, OFF: WDT disable
 */
#pragma config WDTE = ON

/*
 * PWRTE Power-up Timer Enable bit
 * ON: PWRT enable, OFF: PWRT disable
 */
#pragma config PWRTE = ON

/*
 * CP FLASH Program Memory Code Protection bits
 * OFF: Code protection off
 * UPPER_256: 1F00h to 1FFFh code protected
 * HALF: 1000h to 1FFFh code protected
 * ALL: 0000h to 1FFFh code protected
 */
//#pragma config CP = ALL
#pragma config CP = OFF

/*
 * BOREN Brown-out Reset Enable bit
 * ON: BOR enable, OFF: BOR disable
 */
#pragma config BOREN = ON

/*
 * LVP 	Low Voltage In-Circuit Serial Programming Enable bit
 * ON: RB3/PGM pin has PGM function; low-voltage programming enabled
 * OFF: RB3 is digital I/O, HV on MCLR must be used for programming
 */
#pragma config LVP = ON

/*
 * CPD Data EE Memory Code Protection
 * OFF: Code Protection off, ON: Data EEPROM memory code-protected
 */
#pragma config CPD = OFF

/*
 * WRT FLASH Program Memory Write Enable
 * ON: Unprotected program memory may be written to by EECON control
 * OFF: Unprotected program memory may not be written to by EECON control
 */
#pragma config WRT = ON

/*
 * DEBUG In-Circuit Debugger Mode bit
 * OFF: In-Circuit Debugger disabled, RB6 and RB7 are general purpose I/O pins
 * ON: In-Circuit Debugger enabled, RB6 and RB7 are dedicated to the debugger
 * 
 * Warning: The hex file has the debug bit set.  The debug bit has been cleared during load to memory. 
 * The original hex file has not been modified.
 */
#pragma config DEBUG = OFF

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* DEVICE_CONFIG_H */

