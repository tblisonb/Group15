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
#include "mcc_generated_files/include/pin_manager.h"
#include <stdlib.h>
#include "wire.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/delay.h"

/*
    Main application
*/
int main(void)
{
    SYSTEM_Initialize();
    init_wire(); // initialize RN4870
    
    while (1) {
        volatile uint8_t buffer[64];
        read_data(buffer); // blocking call
        /*
         * The following is placeholder code for interpreting the input
        for (unsigned int i = 0; i < num_types_of_wire; i++) {
         for (unsigned int j = 0; j < num_of_single_type; j++) {
          extrude(length_of_the_given_wire);
         }
         retract(length_to_release_wire);
         while(flag); //wait for user to change type of wire and press continue
        }
        */
    }
}