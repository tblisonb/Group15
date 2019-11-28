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
#include <time.h>

/*
    Main application
*/
int main(void)
{
    
    // ----- INITIALIZATIONS ----- //
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    int oldA = IO_PE0_GetValue(); //get the initial value of clkPin
    int oldB = IO_PE1_GetValue() >> 1; //get the initial value of dtPin
    unsigned int state = 2; // tracks by clockwise turns 
    
    time_t start;   // Variable used to see the execution time
    time_t end;
    double total_time;
    char str[50];   // for USART double type variable print purposes

    // ----- MAIN EVENT LOOP ----- //
    while (1){
        unsigned char result = 0;
        unsigned char newA = IO_PE0_GetValue();//read the value of clkPin to newA
        unsigned char newB = IO_PE1_GetValue() >> 1;//read the value of dtPin to newB
        //Sense falling edge of clkPin
        time(&start);
        // Want to have a timer set up to find the response between recognized signals
        // and the program decode of turn direction - US 66
        if (oldA == 0 && newA == 1) {
            
            if (oldB == newB && oldB == 0) {
                time(&end);
                total_time = difftime(end,start);
                printf("Clockwise turn detected\r\n");
                sprintf(str,"%f",total_time);
                printf("  sec to detect: %s\r\n",str);
            } else if (oldB == newB && oldB == 1) {
                time(&end);
                total_time = difftime(end,start);
                printf("Counter-clockwise turn detected\r\n");
                sprintf(str,"%f",total_time);
                printf("  sec to detect: %s\r\n",str);
            }
        }
        if (oldA == 1 && newA == 0) {
           
            if (oldB == newB && oldB == 1) {
                time(&end);
                total_time = difftime(end,start);
                printf("Clockwise turn detected\r\n");
                sprintf(str,"%f",total_time);
                printf("  sec to detect: %s\r\n",str);
            } else if (oldB == newB && oldB == 0) {
                time(&end);
                total_time = difftime(end,start);
                printf("Counter-clockwise turn detected\r\n");
                sprintf(str,"%f",total_time);
                printf("  sec to detect: %s\r\n",str);
            }
            //increment the state or decrement the state based on result, 
            //state can never be negative or greater then 31
            result = (oldB * 8) - 1; 
        }
        //increment the state or decrement the state based on result, 
        //state can never be negative or greater then 7
        state = (state + result) % 32;
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