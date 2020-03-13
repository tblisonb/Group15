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
#include "RN487x.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/delay.h"

void led_blink(int num_times) {
    for (int i = 0; i < num_times; i++) {
        IO_PF5_SetHigh();
        DELAY_milliseconds(200);
        IO_PF5_SetLow();
        DELAY_milliseconds(200);
    }
    DELAY_milliseconds(800);
}

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    led_blink(10);
    /*
     * The following control will spin the stepper motor 5 steps at a time with
     * a delay in between each 5 step increment.
     */
    RN487X_Init();
    RN487X_EnterCmdMode();
    uint8_t cmd_buf[16];
    
    cmd_buf[0] = 'S';
    cmd_buf[1] = 'S';
    cmd_buf[2] = ',';
    cmd_buf[3] = 'C';
    cmd_buf[4] = 'O';
    cmd_buf[5] = '\n';
    cmd_buf[6] = '\r';
    
    RN487X_SendCmd(cmd_buf, 7); // enable device info & T-UART services
    
    cmd_buf[0] = 'A';
    cmd_buf[1] = 'O';
    cmd_buf[2] = 'K';
    cmd_buf[3] = '\n';
    cmd_buf[4] = '\r';
    
    //while (!(RN487X_ReadMsg(cmd_buf, 5)));
    
    RN487X_RebootCmd();
    DELAY_milliseconds(RN487X_STARTUP_DELAY);
    
    cmd_buf[0] = 'S';
    cmd_buf[1] = '-';
    cmd_buf[2] = ',';
    cmd_buf[3] = 'C';
    cmd_buf[4] = 'o';
    cmd_buf[5] = 'i';
    cmd_buf[6] = 'l';
    cmd_buf[7] = ' ';
    cmd_buf[8] = 'W';
    cmd_buf[9] = 'i';
    cmd_buf[10] = 'n';
    cmd_buf[11] = 'd';
    cmd_buf[12] = '\n';
    cmd_buf[13] = '\r';
    
    RN487X_SendCmd(cmd_buf, 14);
    const char msg[16];
    RN487X_WaitForMsg(msg, 16);
    printf("received");
    while (1) {
        IO_PF5_Toggle();
        DELAY_milliseconds(50);
    }
}