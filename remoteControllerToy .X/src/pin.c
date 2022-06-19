/*
 * File:   pin.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 12:35 PM
 */


#include <xc.h>
#include "pin.h"

void PinInitialize(void) {
    // PORTA [5:0]
    ADCON1 = 0b00000110; // All digital I/O
    PORTA = 0b00000000; // Output Cleared
    TRISA = 0b11000000; // All Output
    
    // PORTB [7:0]
    PORTB = 0b00000000; // Output Cleared
    TRISB = 0b00000000; // All Output
    
    // PORTC [7:0]
    PORTC = 0b00000000; // Output Cleared
    TRISC = 0b00000000; // All Output

    // PORTD [7:0]
    PORTD = 0b00000000; // Output Cleared
    TRISD = 0b00000000; // All Output

    // PORTE [2:0]
    PORTE = 0b00000000; // Output Cleared
    TRISE = 0b00000000; // All Output, general purpose I/O mode

}
