/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include "stepper.h"
#include "actuator.h"
#include "mcc_generated_files/include/pin_manager.h"

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    /*
     * The following control will spin the stepper motor 5 steps at a time with
     * a delay in between each 5 step increment.
     */
    
    while (1) {
        // Turn the stepper motor 5 steps in the clockwise direction
        cw_turn(&PORTB, 5, 200);
        _delay_ms(1000);
        
        // Pulse the actuator with a length of 0.5 seconds
        actuator_pulse(&PORTF, 2, 5);
        _delay_ms(1000);
        // Return the actuator to the extended position
        actuator_extend(&PORTF, 2);
        
        // Turn the stepper motor 5 steps in the counterclockwise direction
        cc_turn(&PORTB, 5, 200);
        _delay_ms(1000);
        
        // Send an inverted pulse to the actuator with a length of 0.5 seconds
        actuator_pulse_inv(&PORTF, 2, 5);
        _delay_ms(1000);
        // Return the actuator to the released position
        actuator_release(&PORTF, 2);
    }
}
/**
    End of File
*/