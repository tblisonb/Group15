/*
 * File:   main.c
 * Author: tblisonb
 *
 * Created on February 5, 2020, 7:06 PM
 */

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include "wire.h"


int main(void) {
    
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    /*
     * The following control will spin the stepper motor 5 steps at a time with
     * a delay in between each 5 step increment.
     */
    
    while (1) {
        extrude_min_step(); // single step the stepper motor
        extrude(50); // extrude 50 mm of wire
        cut();       // cut wire at current length
        retract(10); // retract 10 mm of wire
        retract_min_step(); // single step the stepper motor
    }
}


