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

#include "../include/usart3.h"

#if defined(__GNUC__)

int USART3_printCHAR(char character, FILE *stream)
{
    USART3_Write(character);
    return 0;
}

FILE USART3_stream = FDEV_SETUP_STREAM(USART3_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
    USART0_Write(outChar);
    return outChar;
}
#endif

void USART3_Initialize()
{
    //set baud rate register
    USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);
	
    //RXCIE disabled; TXCIE disabled; DREIE disabled; RXSIE disabled; LBME disabled; ABEIE disabled; RS485 OFF; 
    USART3.CTRLA = 0x00;
	
    //RXEN disabled; TXEN enabled; SFDEN disabled; ODME disabled; RXMODE NORMAL; MPCM disabled; 
    USART3.CTRLB = 0x40;
	
    //CMODE ASYNCHRONOUS; PMODE DISABLED; SBMODE 1BIT; CHSIZE 8BIT; UDORD disabled; UCPHA disabled; 
    USART3.CTRLC = 0x03;
	
    //DBGCTRL_DBGRUN
    USART3.DBGCTRL = 0x00;
	
    //EVCTRL_IREI
    USART3.EVCTRL = 0x00;
	
    //RXPLCTRL_RXPL
    USART3.RXPLCTRL = 0x00;
	
    //TXPLCTRL_TXPL
    USART3.TXPLCTRL = 0x00;
	

#if defined(__GNUC__)
    stdout = &USART3_stream;
#endif

}

void USART3_Enable()
{
    USART3.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART3_EnableRx()
{
    USART3.CTRLB |= USART_RXEN_bm;
}

void USART3_EnableTx()
{
    USART3.CTRLB |= USART_TXEN_bm;
}

void USART3_Disable()
{
    USART3.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART3_GetData()
{
    return USART3.RXDATAL;
}

bool USART3_IsTxReady()
{
    return (USART3.STATUS & USART_DREIF_bm);
}

bool USART3_IsRxReady()
{
    return (USART3.STATUS & USART_RXCIF_bm);
}

bool USART3_IsTxBusy()
{
    return (!(USART3.STATUS & USART_TXCIF_bm));
}

bool USART3_IsTxDone()
{
    return (USART3.STATUS & USART_TXCIF_bm);
}

uint8_t USART3_Read()
{
    while (!(USART3.STATUS & USART_RXCIF_bm))
            ;
    return USART3.RXDATAL;
}

void USART3_Write(const uint8_t data)
{
    while (!(USART3.STATUS & USART_DREIF_bm))
            ;
    USART3.TXDATAL = data;
}