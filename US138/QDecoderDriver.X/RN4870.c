/* 
 * File:   RN4870.c
 * Author: tblisonb
 *
 * Created on March 6, 2020, 12:41 PM
 */
#include "RN4870.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcc_generated_files/BLE2_driver.h"
#include "mcc_generated_files/drivers/uart.h"
#include "mcc_generated_files/mcc.h"

#define responseBufferSize  31

static uint8_t rn4020ResponseIndex = 0;
static char rn4020ResponseBuffer [responseBufferSize] = {0};
static char exampleReadStorage [responseBufferSize] = {0};

void send_message(const char *message){
    if(BLE2_isConnected()){
        BLE2_SendString(message);
    }
}

void send_buffer(uint8_t *buffer, uint8_t len)
{
    if(BLE2_isConnected()){
        BLE2_SendBuffer(buffer, len);
    }
}

void init_BLE(const char* name)              // Call After System Init; Above while(1) Loop in Main.c
{   
    char* exampleRead;
    uart[BLE2].SetRxISR(capture_received_message);
    BLE2_WakeModule();                       // Wake Module using GPIO       
    blocking_wait(20);                       // Wait for "CMD" Response              
    exampleRead = get_response();            // Read "CMD\r\n" from Buffer
    strcpy(exampleReadStorage, exampleRead); // Store for use/reference
    ready_receive_buffer();                  // Prepare for next message
    BLE2_EnterCommand_Mode();                // Enter "Command Mode" via GPIO
    blocking_wait(10);
    send_and_wait("SF,1\r\n");               // Factory Reset
    send_and_wait("SR,30000800\r\n");        // Setup Services
    BLE2_SendString("SN,");                  // Set Name
    BLE2_SendString(name);
    send_and_wait("\r\n");
    send_and_wait("R,1\r\n");                // Reset
    blocking_wait(20);
    BLE2_ExitCommand_Mode();                 // Exit "Command Mode" via GPIO
}

void capture_received_message(void)           // Call in ISR EUSART RX after EUSART_Receive_ISR() 
{
    uart[BLE2].RxDefaultISR();
    uint8_t readByte = uart[BLE2].Read();
    if (rn4020ResponseIndex == responseBufferSize)
    {
        ready_receive_buffer();
    }
    if (readByte != '\0' && rn4020ResponseIndex < responseBufferSize)
    {
        rn4020ResponseBuffer[rn4020ResponseIndex++] = readByte;
    }
}

void ready_receive_buffer (void)
{
    rn4020ResponseIndex = 0;
    for (uint8_t position = 0; position < responseBufferSize; position++)
    {
        rn4020ResponseBuffer[position] = 0;
    }
}

char* get_response(void)
{
    return rn4020ResponseBuffer;
}

void blocking_wait (uint16_t limit)
{
    for (uint16_t counter = 0; counter < limit; counter++)
    {
        DELAY_milliseconds(15);
    }
}

char* send_and_wait(const char* sendString)
{
    BLE2_SendString(sendString);
    blocking_wait(4);                 // Wait for Response (~60ms)
    return get_response();            // Read String from Buffer
}