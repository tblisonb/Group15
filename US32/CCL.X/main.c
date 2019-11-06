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
    unsigned int state = 0;
    char activate = 0;
    /* Replace with your application code */
    while (1){
        if(((IO_PC4_GetValue() >> 4) == 1) && ((IO_PD4_GetValue() >> 4) == 1)){
            activate = 1;
        }
        else if((IO_PC4_GetValue() == 0) && (IO_PD4_GetValue() == 0)){
            activate = 0;
        }
        else if(((IO_PC4_GetValue() >> 4) == 1) && (IO_PD4_GetValue() == 0) && (activate == 1)){
            state = (state + 1) % 4;
            activate = 0;
        }
        else if(((IO_PD4_GetValue() >> 4)== 1) && (IO_PC4_GetValue() == 0) && (activate == 1)){
            state = (state - 1) % 4;
            activate = 0;
        }
        VPORTE.OUT = 1 << state;
        if(activate == 1){
            IO_PF5_SetHigh();
        }
        else{
            IO_PF5_SetLow();
        }
        IO_PF5_SetHigh();
    }
}
/**
    End of File
*/