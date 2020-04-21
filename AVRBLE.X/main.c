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
#include "rn487x_interface.h"
#include "rn487x.h"
/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    DELAY_milliseconds(200);
    
    RN487X_Init();              // initialize BLE HW module
    DELAY_milliseconds(200);    // allow module to process commands
    RN487X_EnterCmdMode();      // enter command mode
    DELAY_milliseconds(200);    // processing time
    uint8_t cmd_buf[16];        // command buffer
    
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
    DELAY_milliseconds(200);

    /* Replace with your application code */
    int idx = 0;
    unsigned char msg[16];
    while (1){
        DELAY_milliseconds(500);
        if (RN487X_DataReady()) {
            msg[idx++] = RN487X_Read();
            IO_PF5_SetHigh();
            DELAY_milliseconds(250);
            IO_PF5_SetLow();
        }
        if (idx == 15) {
            IO_PF5_SetHigh();
            DELAY_milliseconds(1000);
            IO_PF5_SetLow();
            idx = 0;
        }
    }
    return 0;
}
/**
    End of File
*/