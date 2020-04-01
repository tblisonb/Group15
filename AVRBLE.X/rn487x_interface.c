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

#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/include/usart0.h"
#include "rn487x_interface.h"

static bool connected = false;

static void RN487X_ResetSet(bool);
static void RN487X_ResetSetLow(void);
static void RN487X_RxIndSet(bool);
static void RN487X_RxIndSetLow(void);
static void RN487X_ModeSet(bool);
static bool RN487X_ModeGet(void);
static void RN487X_MessageHandler(char* message);

/**
  Section: Global Variables
 */

const iRN487X_FunctionPtrs_t RN487X = {
    .uartTx = USART0_Write,
    .uartRx = USART0_Read,
    .isTxDone = USART0_IsTxReady,
    .isRxReady = USART0_IsRxReady,
    .rxIndSet = RN487X_RxIndSet,
    .rstSet = RN487X_ResetSet,
    .modeSet = RN487X_ModeSet,
    .modeGet = RN487X_ModeGet,
    .delayMs = DELAY_milliseconds,
    .asyncHandler = RN487X_MessageHandler
};

bool RN487X_IsConnected(void)
{
    return connected;
}

/*
 *  Interface APIs
 */

static void RN487X_ResetSet(bool value)
{
    if (value)
    {
        BT_RST_SetHigh();
    }
    else
    {
        BT_RST_SetLow();
    }
}

static void RN487X_ResetSetLow(void)
{
    BT_RST_SetLow();
}

static void RN487X_RxIndSet(bool value)
{
    if (value)
    {
        BT_RX_IND_SetHigh();
    }
    else
    {
        BT_RX_IND_SetLow();
    }
}

static void RN487X_RxIndSetLow(void)
{
    BT_RX_IND_SetLow();
}

static void RN487X_ModeSet(bool value)
{
    //Set as output pin
    SW0_SetDigitalOutput();

    if (value)
    {
        SW0_SetHigh();
    }
    else
    {
        SW0_SetLow();
    }
}

static bool RN487X_ModeGet(void)
{
    //Set as input pin
    SW0_SetDigitalInput();
    //Read and return pin status
    return (SW0_GetValue());
}

static void RN487X_MessageHandler(char* message)
{
    printf("<<< %s >>> \r\n", message);
    if (strstr(message, "DISCONNECT"))
    {
        connected = false;
        puts("]");
    }
    else if (strstr(message, "STREAM_OPEN"))
    {
        connected = true;
        puts("[");
    }
}