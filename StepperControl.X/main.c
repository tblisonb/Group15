/*
 * File:   main.c
 * Author: tblisonb
 *
 * Created on February 5, 2020, 7:06 PM
 */

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include "stepper.h"


int main(void) {
    
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    /*
     * The following control will spin the stepper motor 5 steps at a time with
     * a delay in between each 5 step increment.
     */
    
    while (1) {
        // Turn the stepper motor 5 steps in the clockwise direction
        cw_turn(&PORTD, 5, 200);
        _delay_ms(1000);
        
        // Pulse the actuator with a length of 0.5 seconds
        actuator_pulse(&PORTC, 0, 5);
        _delay_ms(1000);
        // Return the actuator to the extended position
        actuator_extend(&PORTC, 0);
        
        // Turn the stepper motor 5 steps in the counterclockwise direction
        cc_turn(&PORTD, 5, 200);
        _delay_ms(1000);
        
        // Send an inverted pulse to the actuator with a length of 0.5 seconds
        actuator_pulse_inv(&PORTC, 0, 5);
        _delay_ms(1000);
        // Return the actuator to the released position
        actuator_release(&PORTC, 0);
    }
}


