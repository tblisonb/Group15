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
#include "stepper.h"
#include "servo.h"
#include "RN487x.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/delay.h"
#include "jsmn.h"

#define NUM_TOKENS 3
#define END_LEN 5
#define DEBUG

int int_pow(int b, int exp) {
    int result = 1;
    while (exp) {
        if (exp % 2)
           result *= b;
        exp /= 2;
        b *= b;
    }
    return result;
}

unsigned int hex_to_int(char* hex, int start, int end) {
    unsigned int result = 0;
    unsigned int i;
    for (i = end; i >= start; i--) {
        int value = 0;
        if (hex[i] >= '0' && hex[i] <= '9')
            value = hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            value = hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            value = hex[i] - 'a' + 10;
        result += int_pow(value, (end - start) - (i - start) + 1);
    }
    return result;
}

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    DELAY_milliseconds(RN487X_STARTUP_DELAY);
    
    RN487X_Init();              // initialize BLE HW module
    DELAY_milliseconds(200);    // allow module to process commands
    /*
    RN487X_EnterCmdMode();      // enter command mode
    DELAY_milliseconds(200);    // processing time
    uint8_t cmd_buf[16];        // command buffer
    
    // command to set the name of the device as "Coil_Wind"
    cmd_buf[0] = 'S';
    cmd_buf[1] = '-';
    cmd_buf[2] = ',';
    cmd_buf[3] = 'C';
    cmd_buf[4] = 'o';
    cmd_buf[5] = 'i';
    cmd_buf[6] = 'l';
    cmd_buf[7] = '_';
    cmd_buf[8] = 'W';
    cmd_buf[9] = 'i';
    cmd_buf[10] = 'n';
    cmd_buf[11] = 'd';
    cmd_buf[12] = '\n';
    cmd_buf[13] = '\r';
    
    RN487X_SendCmd(cmd_buf, 14);    // send the command to the BLE module
    DELAY_milliseconds(200);        // processing time
    
    // command to enable "Transparent UART" service
    cmd_buf[0] = 'S';
    cmd_buf[1] = 'S';
    cmd_buf[2] = ',';
    cmd_buf[3] = 'C';
    cmd_buf[4] = 'O';
    cmd_buf[5] = '\n';
    cmd_buf[6] = '\r';
    
    RN487X_SendCmd(cmd_buf, 7); // enable device info & T-UART services
    DELAY_milliseconds(200);
    RN487X_RebootCmd();         // reboot the device for the changes made
    DELAY_milliseconds(RN487X_STARTUP_DELAY);
    led_blink(2);               // ready signal
    */
    
    //Call the ISR of RTC for the RE turns
    /*
    uint8_t wireLength = RN487X_Read(); //may not be correct
    //Placeholder equation for figuring out how many turns are needed
    int encoderTurns = (0.05 * wireLength);
    
    int count = 0;
    int targetCount = encoderTurns;
    if(count == targetCount) {
        ISR(RTC_CNT_vect);
    }*/
    
    
    int idx = 0;
    char msg[64];
#ifndef DEBUG
    bool state = 0; // 0 = data receiving mode, 1 = extrusion mode
    static jsmn_parser parser;
    static jsmntok_t tokens[NUM_TOKENS];
    jsmn_init(&parser);
    unsigned int object_size;
    unsigned int wire_data[NUM_TOKENS]; // [gauge, quantity, length]
#endif
    while (1) {
#ifdef DEBUG
        if (RN487X_DataReady()) {
            msg[idx++] = (unsigned char) RN487X_Read();
        } else if (idx >= 4) {
            if (msg[0] == 'c' && msg[1] == 'c')
                cc_turn((volatile unsigned char*)&PORTE.OUT, hex_to_int(msg, 2, 3) * 10, 10);
            else if (msg[0] == 'c' && msg[1] == 'w')
                cw_turn((volatile unsigned char*)&PORTE.OUT, hex_to_int(msg, 2, 3) * 10, 10);
            else if (msg[0] == 's' && msg[1] == 'c')
                rotate(105);
            else if (msg[0] == 's' && msg[1] == 's')
                rotate(90);
            else if (msg[0] == 's' && msg[1] == 'n')
                rotate(0);
            idx = 0;
        } else if (idx > 63) {
            idx = 63;
        }
#else
        if (RN487X_DataReady() && !state) {
            msg[idx] = (unsigned char) RN487X_Read();
            if (msg[idx] == '}')   // end of json object
                state = 1;
            idx++;
        } else {
            if ((object_size = jsmn_parse(&parser, msg, idx, tokens, NUM_TOKENS)) >= 0) { // indicates success
                unsigned char i;
                for (i = 0; i < NUM_TOKENS; i++) { // get each token value
                    unsigned char j;
                    char nums[tokens[i].size]; // buffer for value chars
                    for (j = 0; j < tokens[i].size; j++) {
                        nums[j] = msg[tokens[i].start + j]; // deep copy value chars from msg
                    }
                    wire_data[i] = hex_to_int(nums, 0, tokens[i].size - 1); // convert chars to integer
                }
                // loop as many times as there are pieces of wire to extrude
                for (i = 0; i < wire_data[1]; i++) {
                    // extrude stripped end length
                    cc_turn((volatile unsigned char*)&PORTE.OUT, mm_to_steps(END_LEN), 10);
                    // strip
                    rotate(90);
                    DELAY_milliseconds(500);
                    // extrude wire for "length" piece
                    cc_turn((volatile unsigned char*)&PORTE.OUT, mm_to_steps(wire_data[2]), 10);
                    // strip
                    rotate(90);
                    DELAY_milliseconds(500);
                    // cut
                    rotate(105);
                    DELAY_milliseconds(500);
                }
                rotate(0); // reset servo
            } else { // parse failed
                // error LED on
            }
            idx = 0; // reset buffer
        }
#endif
    }
}