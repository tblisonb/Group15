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
#include <util/delay.h>

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    int oldA = IO_PE0_GetValue(); //get the initial value of clkPin
    int oldB = IO_PE1_GetValue() >> 1; //get the initial value of dtPin
    unsigned char state = 2;
    
    IO_PE1_SetHigh();
    _delay_ms(1000);
    IO_PE1_SetLow();

    /* Replace with your application code */
    while (1){
        unsigned char result = 0;
        unsigned char newA = IO_PE0_GetValue();//read the value of clkPin to newA
        unsigned char newB = IO_PE1_GetValue() >> 1;//read the value of dtPin to newB
        //increment the state or decrement the state based on result, 
        //state can never be negative or greater then 7
        state = (state + result) % 32;
        //Sense falling edge of clkPin
        if (oldA == 0 && newA == 1) {
            if (oldB == newB && oldB == 0) {
                //printf("Clockwise turn detected");
                USART0_Write(state);
            } else if (oldB == newB && oldB == 1) {
                //printf("Counter-clockwise turn detected");
                USART0_Write(state);
            }
        }
        if (oldA == 1 && newA == 0) {
            if (oldB == newB && oldB == 1) {
                //printf("Clockwise turn detected");
                USART0_Write(state);
            } else if (oldB == newB && oldB == 0) {
                //printf("Counter-clockwise turn detected");
                USART0_Write(state);
            }
            //increment the state or decrement the state based on result, 
            //state can never be negative or greater then 31
            result = (oldB * 8) - 1; 
        }
        //store the new state of clkPin and dtPin for the next cycle through
        oldA = newA;
        oldB = newB;
        //display the state to the connected lights
        VPORTF.OUT = state;
    }
}
/**
    End of File
*/