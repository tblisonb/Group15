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
#include <util/delay.h>
#include <avr/io.h>

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    

    int *ctrl = 0;
    int *ctrlB = 0;
    unsigned int state = 0;
    SYSTEM_Initialize(ctrl, ctrlB);
    /* Replace with your application code */
    int oldA = IO_PF2_GetValue() >> 2;
    int oldB = IO_PF2_GetValue() >> 3;
    
    while (1){
        while(1) {
            //IO_PF5_Toggle();
        int result = 0;
        int newA = *ctrl;
        int newB = *ctrlB;
        
        if(IO_PF2_GetValue() == 1){
            ctrlB = 0;
        } else {
            ctrlB = 1;
        }
        
        if(oldA == 1 && newA == 0) {
            result = (oldB * 2) - 1;
            ctrlB = 1;
            printf("%i\n", result);    
        } 
        
        state = (state + result) % 3;
        if(state == 0) {
            IO_PD3_SetHigh();
            IO_PD4_SetLow();
            IO_PD5_SetLow();
        } else if(state == 1) {
            IO_PD5_SetHigh();
            IO_PD3_SetLow();
            IO_PD4_SetLow();
        } else {
            IO_PD4_SetHigh();
            IO_PD3_SetLow();
            IO_PD5_SetLow();
        }
        
        oldA = newA;
        oldB = newB;
    }
}
        
}
/**
    End of File
*/