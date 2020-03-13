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
#ifndef RN487X_INTERFACE_H
#define	RN487X_INTERFACE_H
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    // RN487x UART interface control
    void (*uartTx)(uint8_t);
    uint8_t (*uartRx)(void);
    bool (*isTxDone)(void);
    bool (*isRxReady)(void);
    // RN487x RX_IND pin control
    void (*rxIndSet)(bool);
    // RN487x Reset pin control
    void (*rstSet)(bool);
    // RN487x Mode pin set
    void (*modeSet)(bool);
    // RN487x Mode pin get
    bool (*modeGet)(void);
    // Delay API
    void (*delayMs)(uint16_t);
    // Status Message Handler
    void (*asyncHandler)(char*);
}iRN487X_FunctionPtrs_t;

extern const iRN487X_FunctionPtrs_t RN487X;

bool RN487X_IsConnected(void);

#endif	/* RN487X_INTERFACE_H */

