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
    
    volatile unsigned char state = STATE1;
    
    while (1) {
        state = cw_step((volatile unsigned char*)&PORTD.OUT, state);
        _delay_ms(1000);
    }
}


