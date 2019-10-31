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
#include "mcc_generated_files/include/pin_manager.h"
#include <avr/io.h>

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    int oldA = IO_PF2_GetValue() >> 2; //get the initial value of clkPin
    int oldB = IO_PF3_GetValue() >> 3; //get the initial value of dtPin
    unsigned int state = 2;

    /* Replace with your application code */
    while (1){
        int result = 0;
        int newA = IO_PF2_GetValue() >> 2;//read the value of clkPin to newA
        int newB = IO_PF3_GetValue() >> 3;//read the value of dtPin to newB
        //Sense change in state
        if(oldA != newA || oldB != newB){
            IO_PF5_Toggle();
            //send state information using usart
            printf("%i -> %i\t%i -> %i\n", oldA, newA, oldB, newB);
            //Sense falling edge of clkPin
            if (oldA == 1 && newA == 0)
            {
                //If clkPin was the first to return to zero return 1, else return -1
                result = (oldB * 2) - 1;
                //send directional information using usart
                if(result == 1){
                    printf("R\n");
                }
                else if(result != 1){
                    printf("L\n");
                }
            }
        }
        //increment the state or decrement the state based on result, 
        //state can never be negative or greater then 7
        state = (state + result) % 8;
        //store the new state of clkPin and dtPin for the next cycle through
        oldA = newA;
        oldB = newB;
        //display the state to the connected lights
        VPORTD.OUT = 1 << state;
    }
}
/**
    End of File
*/