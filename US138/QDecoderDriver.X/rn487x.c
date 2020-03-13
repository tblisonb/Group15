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

/**
  Section: Included Files
 */
#include <stdio.h>
#include "../mcc.h"
#include "rn487x.h"

#define STATUS_MESSAGE_DELIMITER        '%'

/**
  Section: Global Variables
 */
//Command TX buffer
uint8_t cmdBuf[64];

static char *buffer;
static uint8_t bufSize;
static char *pHead;
static uint8_t peek = 0;
static bool dataReady = false;

static bool RN487X_FilterData(void);

/**
  Section: RN487x APIs
 */
bool RN487X_Init(void)
{
    /* In PIC-BLE, mode pin is connected with SW0 and the interface pin on the
     * host MCU is configured as input pin.
     * Since the RN487x needs to be set to application mode  during
     * initialization, the interface pin on the host MCU is set as output pin
     * and drive high.  */
    if (!RN487X.modeGet())
    {
        // Configure as output pin and drive high to set application mode
        RN487X.modeSet(true);
    }

    //Enter reset
    RN487X.rstSet(false);
    //Keep the reset pin low
    RN487X.delayMs(RN487X_RESET_LOW_DELAY_TIME);
    //Exit reset
    RN487X.rstSet(true);

    /* Since the mode pin is connected to SW0 in PIC-BLE, the host interface
     * for mode pin is reconfigured as input pin. This may not be the
     * case in other hardwares */
    RN487X.modeGet();

    //Wakeup
    RN487X.rxIndSet(false);
    //Wait while RN487X is booting up
    RN487X.delayMs(RN487X_STARTUP_DELAY);

    //Remove unread data sent by RN487x, if any
    while (RN487X.isRxReady())
    {
        RN487X.uartRx();
    }

    return true;
}

// TODO: This function would be no different if sending data. Consider renaming.
void RN487X_SendCmd(const uint8_t *cmd, uint8_t cmdLen)
{
    uint8_t index = 0;

    while (index < cmdLen)
    {
        if (RN487X.isTxDone())
        {
            RN487X.uartTx(cmd[index]);
            index++;
        }
    }
}

uint8_t RN487X_GetCmd(const char *getCmd, uint8_t getCmdLen, char *getCmdResp)
{
    uint8_t index = 0;

    RN487X_SendCmd((uint8_t *) getCmd, getCmdLen);

    do
    {
        getCmdResp[index++] = RN487X.uartRx();
    }
    while (getCmdResp[index - 1] != '\n');

    return index;
}

bool RN487X_ReadMsg(const uint8_t *expectedMsg, uint8_t msgLen)
{
    uint8_t index;
    uint8_t resp;

    for (index = 0; index < msgLen; index++)
    {
        resp = RN487X.uartRx();
        if (resp != expectedMsg[index])
        {
            return false;
        }
    }

    return true;
}

bool RN487X_ReadDefaultResponse(void)
{
    uint8_t resp[3];
    bool status = false;

    resp[0] = RN487X.uartRx();
    resp[1] = RN487X.uartRx();
    resp[2] = RN487X.uartRx();

    switch (resp[0])
    {
        case 'A':
        {
            if ((resp[1] == 'O') && (resp[2] == 'K'))
                status = true;

            break;
        }
        case 'E':
        {
            if ((resp[1] == 'r') && (resp[2] == 'r'))
                status = false;

            break;
        }
        default:
        {
            return status;
        }
    }

    /* Read carriage return and line feed comes with response */
    RN487X.uartRx();
    RN487X.uartRx();

    //Read CMD>
    RN487X.uartRx();
    RN487X.uartRx();
    RN487X.uartRx();
    RN487X.uartRx();
    RN487X.uartRx();
  
    return status;
}

void RN487X_WaitForMsg(const char *expectedMsg, uint8_t msgLen)
{
    uint8_t index = 0;
    uint8_t resp;

    do
    {
        resp = RN487X.uartRx();

        if (resp == expectedMsg[index])
        {
            index++;
        }
        else
        {
            index = 0;
            if (resp == expectedMsg[index])
            {
                index++;
            }
        }
    }
    while (index < msgLen);
}

bool RN487X_EnterCmdMode(void)
{
    const uint8_t cmdPrompt[] = {'C', 'M', 'D', '>', ' '};

    cmdBuf[0] = '$';
    cmdBuf[1] = '$';
    cmdBuf[2] = '$';

    RN487X_SendCmd(cmdBuf, 3);

    return RN487X_ReadMsg(cmdPrompt, sizeof (cmdPrompt));
}

bool RN487X_EnterDataMode(void)
{
    const uint8_t cmdPrompt[] = {'E', 'N', 'D', '\r', '\n'};

    cmdBuf[0] = '-';
    cmdBuf[1] = '-';
    cmdBuf[2] = '-';
    cmdBuf[3] = '\r';
    cmdBuf[4] = '\n';

    RN487X_SendCmd(cmdBuf, 5);

    return RN487X_ReadMsg(cmdPrompt, sizeof (cmdPrompt));
}

bool RN487X_SetOutputs(rn487x_gpio_bitmap_t bitMap)
{
    char ioHighNibble = '0';
    char ioLowNibble = '0';
    char stateHighNibble = '0';
    char stateLowNibble = '0';
    
    // Output pins configurations
    if (bitMap.ioBitMap.p1_3)
    {
        ioHighNibble = '1';
    }
    else
    {
        ioHighNibble = '0';
    }
    ioLowNibble = ( (0x0F & bitMap.ioBitMap.gpioBitMap) + '0');
    
    // High/Low Output settings
    if (bitMap.ioStateBitMap.p1_3_state)
    {
        stateHighNibble = '1';
    }
    else
    {
        stateHighNibble = '0';
    }
    stateLowNibble = ( (0x0F & bitMap.ioStateBitMap.gpioStateBitMap) + '0');

    cmdBuf[0] = '|';    // I/O
    cmdBuf[1] = 'O';    // Output
    cmdBuf[2] = ',';
    cmdBuf[3] = ioHighNibble;       // - | - | - | P1_3
    cmdBuf[4] = ioLowNibble;        // P1_2 | P3_5 | P2_4 | P2_2
    cmdBuf[5] = ',';
    cmdBuf[6] = stateHighNibble;    // - | - | - | P1_3
    cmdBuf[7] = stateLowNibble;     // P1_2 | P3_5 | P2_4 | P2_2
    cmdBuf[8] = '\r';
    cmdBuf[9] = '\n';

    RN487X_SendCmd(cmdBuf, 10);
    return RN487X_ReadDefaultResponse();
}

rn487x_gpio_stateBitMap_t RN487X_GetInputsValues(rn487x_gpio_ioBitMap_t getGPIOs)
{
    char ioHighNibble = '0';
    char ioLowNibble = '0';
    uint8_t ioValue[] = {'0', '0'};
    rn487x_gpio_stateBitMap_t ioBitMapValue;
    ioBitMapValue.gpioStateBitMap = 0x00;
    
    // Output pins configurations
    if (getGPIOs.p1_3)
    {
        ioHighNibble = '1';
    }
    else
    {
        ioHighNibble = '0';
    }
    ioLowNibble = ( (0x0F & getGPIOs.gpioBitMap) + '0');

    cmdBuf[0] = '|';    // I/O
    cmdBuf[1] = 'I';    // Output
    cmdBuf[2] = ',';
    cmdBuf[3] = ioHighNibble;       // - | - | - | P1_3
    cmdBuf[4] = ioLowNibble;        // P1_2 | P3_5 | P2_4 | P2_2
    cmdBuf[5] = '\r';
    cmdBuf[6] = '\n';

    RN487X_SendCmd(cmdBuf, 7);
    RN487X_ReadMsg(ioValue, sizeof (ioValue));    
    ioBitMapValue.gpioStateBitMap = ( (((ioValue[0] - '0') & 0x0F) << 4) | ((ioValue[1] - '0') & 0x0F) );
    return ioBitMapValue;
}

bool RN487X_RebootCmd(void)
{
    const uint8_t reboot[] = {'R', 'e', 'b', 'o', 'o', 't', 'i', 'n', 'g', '\r', '\n'};

    cmdBuf[0] = 'R';
    cmdBuf[1] = ',';
    cmdBuf[2] = '1';
    cmdBuf[4] = '\r';
    cmdBuf[5] = '\n';

    RN487X_SendCmd(cmdBuf, 5);

    return RN487X_ReadMsg(reboot, sizeof (reboot));
}

bool RN487X_Disconnect(void)
{
    cmdBuf[0] = 'K';
    cmdBuf[1] = ',';
    cmdBuf[2] = '1';
    cmdBuf[3] = '\r';
    cmdBuf[4] = '\n';

    RN487X_SendCmd(cmdBuf, 5);

    return RN487X_ReadDefaultResponse();
}

bool RN487X_SetAsyncMessageHandler(char* pBuffer, uint8_t len)
{
    if ((pBuffer != NULL) && (len > 1))
    {
      buffer = pBuffer;
      bufSize = len - 1;
      return true;
    }
    else
    {
        return false;
    }
}

bool RN487X_DataReady(void)
{
    if (dataReady)
    {
        return true;
    }
    
    if (RN487X.isRxReady())
    {
        return RN487X_FilterData();
    }
    return false;
}

uint8_t RN487X_Read(void)
{
    while(RN487X_DataReady() == false); // Wait
    dataReady = false;
    return peek;
}

static bool RN487X_FilterData(void)
{
    static bool asyncBuffering = false;
    
    uint8_t readChar = RN487X.uartRx();
    
    if(asyncBuffering == true)
    {
        if(readChar == STATUS_MESSAGE_DELIMITER)
        {
            asyncBuffering = false;
            *pHead = '\0';
            RN487X.asyncHandler(buffer);
        }
        else if (pHead < buffer + bufSize)
        {
            *pHead++ = readChar;
        }
    }
    else
    {
        if (readChar == STATUS_MESSAGE_DELIMITER)
        {
            asyncBuffering = true;
            pHead = buffer;
        }
        else 
        {
            dataReady = true;
            peek = readChar;
        }
    }
    return dataReady;
}
