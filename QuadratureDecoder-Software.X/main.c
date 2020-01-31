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
 * 
 * @author ASU Capstone Team 15 2019-2020
 * @version 01.2020
*/

/* Includes files */
#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <util/delay.h>

/*
    Main application entry point, no user input
*/
int main(void)
{
    /* Initializes MCU, drivers and middle-ware */
    SYSTEM_Initialize();

    /* Variable declarations/initializations */
    int oldA = IO_PE0_GetValue();       //get the initial value of clkPin (Decoder)
    int oldB = IO_PE1_GetValue() >> 1;  //get the initial value of dtPin  (Decoder)
    unsigned int state = 2;

    /* Infinite execution loop */
    while (1){
        
        /* Loop auto variables */
        unsigned char result = 0;
        unsigned char newA = IO_PE0_GetValue();     //read the value of clkPin to newA
        unsigned char newB = IO_PE1_GetValue() >> 1;//read the value of dtPin to newB
        
        // Sense falling edge of clkPin
        /* Two if statements to account for turns from right to left or vice versa */
        if (oldA == 0 && newA == 1) {
            if (oldB == newB && oldB == 0) {
                printf("Clockwise turn detected\n");
            } else if (oldB == newB && oldB == 1) {
                printf("Counter-clockwise turn detected\n");
            }
            /* Change state based on result */
            result = (oldB * 8) - 1; 
        }
        if (oldA == 1 && newA == 0) {
            if (oldB == newB && oldB == 1) {
                printf("Clockwise turn detected\n");
            } else if (oldB == newB && oldB == 0) {
                printf("Counter-clockwise turn detected\n");
            }
            //increment the state or decrement the state based on result, 
            //state can never be negative or greater then 31
            result = (oldB * 8) - 1; 
        }
        
        /* state is incremented/decremented based on the result, and can
         never be a negative number or greater than 7*/
        state = (state + result) % 32;
        //store the new state of clkPin and dtPin for the next cycle through
        oldA = newA;    // clkPin
        oldB = newB;    // dtPin
        // display the state to the connected LEDs
        VPORTF.OUT = state; // May display VPORT as an error, it will still work fine
    }
}
/**
    End of File
*/