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
#include <string.h>

#define NUM_TOKENS 7
#define END_LEN 5
//#define DEBUG

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

// Ref: https://github.com/zserge/jsmn/blob/master/example/simple.c
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

void USART3_Write_String(char* str, int len) {
    unsigned int i;
    for (i = 0; i < len; i++) {
        USART3_Write(str[i]);
    }
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
    unsigned int quantity = 0;
    unsigned int length = 0;
#endif
    while (1) {
#ifdef DEBUG
        if (RN487X_DataReady()) {
            msg[idx++] = (unsigned char) RN487X_Read();
        } else if (idx >= 4) {
            if (msg[0] == 'c' && msg[1] == 'c')
                cc_turn((volatile unsigned char*)&PORTE.OUT, hex_to_int(msg, 2, 3) * 10, 1);
            else if (msg[0] == 'c' && msg[1] == 'w')
                cw_turn((volatile unsigned char*)&PORTE.OUT, hex_to_int(msg, 2, 3) * 10, 1);
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
        READY_LED_SetHigh();
        if (RN487X_DataReady() && !state) {
            msg[idx] = (char)RN487X_Read();
            STATUS_LED_Toggle();
            USART3_Write(msg[idx]);
            if (msg[idx] == '}' && idx > 5) {  // end of json object
                state = 1;
            } else if (msg[idx] == '}' && idx <= 5) {
                ERROR_LED_SetHigh();
                idx = 0; // reset buffer
            } else {
                idx++;
            }
        } else if (state) {
            ERROR_LED_SetLow();
            READY_LED_SetLow();
            STATUS_LED_SetLow();
            // parse JSON object, stored in tokens[0]
            if ((jsmn_parse(&parser, msg, idx + 1, tokens, NUM_TOKENS)) < 0) { // indicates fail
                ERROR_LED_SetHigh();
                USART3_Write_String("ERROR\n", 6);
            } else {
                unsigned int i;
                quantity = hex_to_int(msg, tokens[4].start, tokens[4].end); // convert chars to integer
                length = hex_to_int(msg, tokens[6].start, tokens[6].end); // convert chars to integer
                USART3_Write('\n');
                USART3_Write_String("Quantity: ", 10);
                USART3_Write('0' + quantity);
                USART3_Write('\n');
                USART3_Write_String("Length: ", 8);
                USART3_Write('0' + length);
                USART3_Write('\n');
                // loop as many times as there are pieces of wire to extrude3
                for (i = 0; i < quantity; i++) {
                    rotate(0);
                    DELAY_milliseconds(100);
                    // extrude stripped end length
                    STATUS_LED_Toggle();
                    cc_turn((volatile unsigned char*)&PORTE.OUT, mm_to_steps(END_LEN), 1);
                    DELAY_milliseconds(100);
                    // strip
                    STATUS_LED_Toggle();
                    rotate(90);
                    DELAY_milliseconds(100);
                    rotate(0);
                    DELAY_milliseconds(100);
                    // extrude wire for "length" piece
                    STATUS_LED_Toggle();
                    cc_turn((volatile unsigned char*)&PORTE.OUT, mm_to_steps(length), 1);
                    DELAY_milliseconds(100);
                    // strip
                    STATUS_LED_Toggle();
                    rotate(90);
                    DELAY_milliseconds(100);
                    rotate(0);
                    DELAY_milliseconds(100);
                    // extrude stripped end length
                    STATUS_LED_Toggle();
                    cc_turn((volatile unsigned char*)&PORTE.OUT, mm_to_steps(END_LEN), 1);
                    DELAY_milliseconds(100);
                    // cut
                    STATUS_LED_Toggle();
                    rotate(105);
                    DELAY_milliseconds(100);
                    rotate(0);
                    DELAY_milliseconds(100);
                }
                cw_turn((volatile unsigned char*)&PORTE.OUT, mm_to_steps(20), 1);
            }
            state = 0;
            idx = 0;
        }
#endif
    }
}