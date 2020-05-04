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
#ifndef RN487X_H
#define	RN487X_H
#include <stdbool.h>
#include <stdint.h>
#include "rn487x_interface.h"    
    
/**
  Section: Macro Declarations
*/

//Time duration to put the RN487X in reset mode
#define RN487X_RESET_LOW_DELAY_TIME    1
//Time delay for RN487X boot up

#define RN487X_STARTUP_DELAY             200

/**
* Union of RN487X gpio BEHAVIOR state (Input/Output)
* Bits (pins) set as (1) are considered OUTPUTS
*/
typedef union
{
    uint8_t gpioBitMap;
    struct
    {
        unsigned p2_2 : 1;          // 01
        unsigned p2_4 : 1;          // 02
        unsigned p3_5 : 1;          // 04
        unsigned p1_2 : 1;          // 08
        unsigned p1_3 : 1;          // 10
        unsigned reserved : 3;
    };
}rn487x_gpio_ioBitMap_t;
/**
* Union of RN487X gpio OUTPUT state (High/Low)
* Bits (states) set as (1) are considered HIGH
*/
typedef union
{
    uint8_t gpioStateBitMap;
    struct
    {
        unsigned p2_2_state : 1;
        unsigned p2_4_state : 1;
        unsigned p3_5_state : 1;
        unsigned p1_2_state : 1;
        unsigned p1_3_state : 1;
        unsigned reserved : 3;
    };
}rn487x_gpio_stateBitMap_t;
/**
* Union of RN487X gpio state & configuration
* Used for I/O (|) related commands
*/
typedef union 
{
    uint16_t gpioMap;
    struct
    {
        rn487x_gpio_ioBitMap_t ioBitMap;
        rn487x_gpio_stateBitMap_t ioStateBitMap;
    };
}rn487x_gpio_bitmap_t;

/**
  Section: RN487x APIs
*/
 /**
  @Summary
    Initializes RN487X Device

  @Description
    This routine initializes RN487x Device.
     
  @Preconditions
    None

  @Param
    None

  @Returns
    bool - true, if init succeeds; false, otherwise 
*/
bool RN487X_Init(void);

 /**
  @Summary
    Sends out command to RN487x.

  @Description
    This routine takes command and its length as input and sends that command 
  * to RN487x.

  @Preconditions
    RN487X_Init() function should have been called before calling this function

  @Param
    cmd  - RN487x command
    cmdLen - RN487x command length

  @Returns
  None
*/
void RN487X_SendCmd(const uint8_t *cmd, uint8_t cmdLen);

 /**
  @Summary
    Gets config value from RN487x by sending get command

  @Description
    This routine gets the config value from RN487x by sending get command.
  * For more details, refer section 2.5 GET COMMANDS in RN4870-71 user guide.

  @Preconditions
    Device should have been in command mode

  @Param
    getCmd  - Get command to send
    getCmdLen - Get command length
    getCmdResp - Buffer to store get command response

  @Returns
    uint8_t - Length of get command response
*/
uint8_t RN487X_GetCmd(const char *getCmd, uint8_t getCmdLen, char *getCmdResp);

 /**
  @Summary
    Reads specific message from RN487x.

  @Description
    This routine takes input from application on the expected response/status 
  * message. It starts read RN487X host interface immediately and look for 
  * expected message.

  @Preconditions
    RN487X_Init() function should have been called before calling this function

  @Param
    expectedMsg  - Expected response/status message from RN487x
    msgLen - Expected response/status message length

  @Returns
    bool - true, if successfully gets expected message; false, otherwise 
*/
bool RN487X_ReadMsg(const uint8_t *expectedMsg, uint8_t msgLen);

 /**
  @Summary
    Waits for specific message from RN487x.

  @Description
    This routine takes input from application on the expected response/status 
  * message. It waits until it receives expected message from RN487x.
  * This helps to read the RN487x status messages.

  @Preconditions
    RN487X_Init() function should have been called before calling this function

  @Param
    expectedMsg  - Expected response/status message from RN487x
    msgLen - Expected response/status message length

  @Returns
    None
*/
void RN487X_WaitForMsg(const char *expectedMsg, uint8_t msgLen);

 /**
  @Summary
    Reads default response from RN487x.

  @Description
    This routine reads RN487x interface for default response which is AOK or ERR. 

  @Preconditions
    RN487X_Init() function should have been called before calling this function.
  * RN487X_SendCmd() function should have been called before this function.

  @Param
    None

  @Returns
    bool - true, if successfully reads default response; false, otherwise
*/
bool RN487X_ReadDefaultResponse(void);

 /**
  @Summary
    Puts the RN487x in command mode.

  @Description
    This routine puts the RN487x in command mode. 

  @Preconditions
    RN487X_Init() function should have been called before calling this function.

  @Param
    None

  @Returns
    bool - true, if successfully enters command mode; false, otherwise
*/
bool RN487X_EnterCmdMode(void);

 /**
  @Summary
    Puts the RN487x in data mode.

  @Description
    This routine puts the RN487x in data mode. 

  @Preconditions
    RN487X_Init() function should have been called before calling this function.

  @Param
    None

  @Returns
    bool - true, if successfully enters data mode; false, otherwise
*/
bool RN487X_EnterDataMode(void);

 /**
  @Summary
    Configures RN487X GPIO pins as output, and sets state

  @Description
    This routine configures the GPIO pins of the RN487X module as Outputs
    This routine configures the High/Low state of pins set as outputs

  @Preconditions
    RN487X_Init() function should have been called before calling this function.

  @Param
    rn487x_gpio_bitmap_t bitMap RN487X GPIO Output I/O & Low/High State

  @Returns
    bool - true, if successfully enters data mode; false, otherwise
*/
bool RN487X_SetOutputs(rn487x_gpio_bitmap_t bitMap);

 /**
  @Summary
    Get RN487X GPIO pins input state status (high/low)

  @Description
    This routine request the GPIO pins state from the RN487X module Inputs
    This routine reads specified GPIO pins current (high/low) state

  @Preconditions
    RN487X_Init() function should have been called before calling this function.

  @Param
    rn487x_gpio_ioBitMap_t getGPIOs RN487X pins to read state status from

  @Returns
    rn487x_gpio_stateBitMap_t - 8bit value coordinated to possible pin options
*/
rn487x_gpio_stateBitMap_t RN487X_GetInputsValues(rn487x_gpio_ioBitMap_t getGPIOs);

 /**
  @Summary
    Resets RN487x.

  @Description
    This routine resets RN487x. For more details, refer R command in 
  * RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    None 

  @Returns
    bool - true, if successfully reboots; false, otherwise
*/
bool RN487X_RebootCmd(void);

 /**
  @Summary
    Disconnects the BLE link between RN487x and remote device.

  @Description
    This routine disconnects the BLE link between RN487x and remote device. 
  * For more details, refer K command in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    None 

  @Returns
    bool - true, if successfully disconnects; false, otherwise
*/
bool RN487X_Disconnect(void);

 /**
  @Summary
    Sets up the Buffer and Buffer Size for Aysnc Message Handler

  @Description
    This routine sets up the Buffer and the Buffer size to be used by the Async
    Message Handler.

  @Preconditions
    None

  @Param
    pBuffer - passed buffer
    len - size of passed buffer 

  @Returns
    bool - true, if able to set buffer and bufSize, false otherwise.
*/
bool RN487X_SetAsyncMessageHandler(char* pBuffer, uint8_t len);

 /**
  @Summary
    Checks to see if there is Data Ready using Async Message Handling

  @Description
    This routine checks to see if there is Data ready on the line using Async Message Handling

  @Preconditions
    RN487X_SetAsyncMessageHandler() must be properly set up.

  @Param
    None

  @Returns
    bool - true, if data is ready, false otherwise.
*/
bool RN487X_DataReady(void);

 /**
  @Summary
    Read incoming Data using Async Message Handling

  @Description
    This routine reads incoming data using Async Message Handling

  @Preconditions
    RN487X_SetAsyncMessageHandler() must be properly set up.

  @Param
    None

  @Returns
    uint8_t - Data Read
*/
uint8_t RN487X_Read(void);

#endif	/* RN487X_H */

