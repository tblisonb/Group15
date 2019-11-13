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

#include "../include/pin_manager.h"
static void (*PORTD_IO_PD5_InterruptHandler)(void);
static void (*PORTF_IO_PF6_InterruptHandler)(void);
static void (*PORTD_IO_PD4_InterruptHandler)(void);
static void (*PORTA_IO_PA1_InterruptHandler)(void);
static void (*PORTF_IO_PF3_InterruptHandler)(void);
static void (*PORTF_IO_PF2_InterruptHandler)(void);
static void (*PORTF_IO_PF5_InterruptHandler)(void);
static void (*PORTD_IO_PD3_InterruptHandler)(void);
static void (*PORTA_IO_PA0_InterruptHandler)(void);
static void (*PORTF_IO_PF4_InterruptHandler)(void);

void PORT_Initialize(void);

int* logic;
int* logicB;

void PIN_MANAGER_Initialize(int* ctrl, int* ctrlB)
{
    logic = ctrl;
    logicB = ctrlB;
    
    PORT_Initialize();

    /* DIR Registers Initialization */
    PORTA.DIR = 0x00;
    PORTB.DIR = 0x00;
    PORTC.DIR = 0x00;
    PORTD.DIR = 0x38;
    PORTE.DIR = 0x00;
    PORTF.DIR = 0x38;

    /* OUT Registers Initialization */
    PORTA.OUT = 0x01;
    PORTB.OUT = 0x00;
    PORTC.OUT = 0x00;
    PORTD.OUT = 0x00;
    PORTE.OUT = 0x00;
    PORTF.OUT = 0x20;

    /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x09;
    PORTA.PIN1CTRL = 0x01;
    PORTA.PIN2CTRL = 0x00;
    PORTA.PIN3CTRL = 0x00;
    PORTA.PIN4CTRL = 0x00;
    PORTA.PIN5CTRL = 0x00;
    PORTA.PIN6CTRL = 0x00;
    PORTA.PIN7CTRL = 0x00;
    PORTB.PIN0CTRL = 0x00;
    PORTB.PIN1CTRL = 0x00;
    PORTB.PIN2CTRL = 0x00;
    PORTB.PIN3CTRL = 0x00;
    PORTB.PIN4CTRL = 0x00;
    PORTB.PIN5CTRL = 0x00;
    PORTB.PIN6CTRL = 0x00;
    PORTB.PIN7CTRL = 0x00;
    PORTC.PIN0CTRL = 0x00;
    PORTC.PIN1CTRL = 0x00;
    PORTC.PIN2CTRL = 0x00;
    PORTC.PIN3CTRL = 0x00;
    PORTC.PIN4CTRL = 0x00;
    PORTC.PIN5CTRL = 0x00;
    PORTC.PIN6CTRL = 0x00;
    PORTC.PIN7CTRL = 0x00;
    PORTD.PIN0CTRL = 0x00;
    PORTD.PIN1CTRL = 0x00;
    PORTD.PIN2CTRL = 0x00;
    PORTD.PIN3CTRL = 0x00;
    PORTD.PIN4CTRL = 0x00;
    PORTD.PIN5CTRL = 0x00;
    PORTD.PIN6CTRL = 0x00;
    PORTD.PIN7CTRL = 0x00;
    PORTE.PIN0CTRL = 0x00;
    PORTE.PIN1CTRL = 0x00;
    PORTE.PIN2CTRL = 0x00;
    PORTE.PIN3CTRL = 0x00;
    PORTE.PIN4CTRL = 0x00;
    PORTE.PIN5CTRL = 0x00;
    PORTE.PIN6CTRL = 0x00;
    PORTE.PIN7CTRL = 0x00;
    PORTF.PIN0CTRL = 0x00;
    PORTF.PIN1CTRL = 0x00;
    PORTF.PIN2CTRL = 0x01;
    PORTF.PIN3CTRL = 0x00;
    PORTF.PIN4CTRL = 0x00;
    PORTF.PIN5CTRL = 0x00;
    PORTF.PIN6CTRL = 0x88;
    PORTF.PIN7CTRL = 0x00;

    /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x00;
    PORTMUX.EVSYSROUTEA = 0x00;
    PORTMUX.TCAROUTEA = 0x00;
    PORTMUX.TCBROUTEA = 0x00;
    PORTMUX.TWISPIROUTEA = 0x00;
    PORTMUX.USARTROUTEA = 0x00;

    // register default ISC callback functions at runtime; use these methods to register a custom function
    PORTD_IO_PD5_SetInterruptHandler(PORTD_IO_PD5_DefaultInterruptHandler);
    PORTF_IO_PF6_SetInterruptHandler(PORTF_IO_PF6_DefaultInterruptHandler);
    PORTD_IO_PD4_SetInterruptHandler(PORTD_IO_PD4_DefaultInterruptHandler);
    PORTA_IO_PA1_SetInterruptHandler(PORTA_IO_PA1_DefaultInterruptHandler);
    PORTF_IO_PF3_SetInterruptHandler(PORTF_IO_PF3_DefaultInterruptHandler);
    PORTF_IO_PF2_SetInterruptHandler(PORTF_IO_PF2_DefaultInterruptHandler);
    PORTF_IO_PF5_SetInterruptHandler(PORTF_IO_PF5_DefaultInterruptHandler);
    PORTD_IO_PD3_SetInterruptHandler(PORTD_IO_PD3_DefaultInterruptHandler);
    PORTA_IO_PA0_SetInterruptHandler(PORTA_IO_PA0_DefaultInterruptHandler);
    PORTF_IO_PF4_SetInterruptHandler(PORTF_IO_PF4_DefaultInterruptHandler);
}

void PORT_Initialize(void)
{
    /* On AVR devices all peripherals are enable from power on reset, this
     * disables all peripherals to save power. Driver shall enable
     * peripheral if used */

    /* Set all pins to low power mode */
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTE + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTF + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTB + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTC + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTD + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
}

/**
  Allows selecting an interrupt handler for PORTD_IO_PD5 at application runtime
*/
void PORTD_IO_PD5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_IO_PD5_InterruptHandler = interruptHandler;
}

void PORTD_IO_PD5_DefaultInterruptHandler(void)
{
    // add your PORTD_IO_PD5 interrupt custom code
    // or set custom function using PORTD_IO_PD5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_IO_PF6 at application runtime
*/
void PORTF_IO_PF6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_IO_PF6_InterruptHandler = interruptHandler;
}

void PORTF_IO_PF6_DefaultInterruptHandler(void)
{
    // add your PORTF_IO_PF6 interrupt custom code
    // or set custom function using PORTF_IO_PF6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTD_IO_PD4 at application runtime
*/
void PORTD_IO_PD4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_IO_PD4_InterruptHandler = interruptHandler;
}

void PORTD_IO_PD4_DefaultInterruptHandler(void)
{
    // add your PORTD_IO_PD4 interrupt custom code
    // or set custom function using PORTD_IO_PD4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_IO_PA1 at application runtime
*/
void PORTA_IO_PA1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_IO_PA1_InterruptHandler = interruptHandler;
}

void PORTA_IO_PA1_DefaultInterruptHandler(void)
{
    // add your PORTA_IO_PA1 interrupt custom code
    // or set custom function using PORTA_IO_PA1_SetInterruptHandler()
    *logicB = IO_PA1_GetValue() >> 1;
}
/**
  Allows selecting an interrupt handler for PORTF_IO_PF3 at application runtime
*/
void PORTF_IO_PF3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_IO_PF3_InterruptHandler = interruptHandler;
}

void PORTF_IO_PF3_DefaultInterruptHandler(void)
{
    // add your PORTF_IO_PF3 interrupt custom code
    // or set custom function using PORTF_IO_PF3_SetInterruptHandler()
    
}
/**
  Allows selecting an interrupt handler for PORTF_IO_PF2 at application runtime
*/
void PORTF_IO_PF2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_IO_PF2_InterruptHandler = interruptHandler;
}

void PORTF_IO_PF2_DefaultInterruptHandler(void)
{
    // add your PORTF_IO_PF2 interrupt custom code
    // or set custom function using PORTF_IO_PF2_SetInterruptHandler()
    
}
/**
  Allows selecting an interrupt handler for PORTF_IO_PF5 at application runtime
*/
void PORTF_IO_PF5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_IO_PF5_InterruptHandler = interruptHandler;
}

void PORTF_IO_PF5_DefaultInterruptHandler(void)
{
    // add your PORTF_IO_PF5 interrupt custom code
    // or set custom function using PORTF_IO_PF5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTD_IO_PD3 at application runtime
*/
void PORTD_IO_PD3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_IO_PD3_InterruptHandler = interruptHandler;
}

void PORTD_IO_PD3_DefaultInterruptHandler(void)
{
    // add your PORTD_IO_PD3 interrupt custom code
    // or set custom function using PORTD_IO_PD3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_IO_PA0 at application runtime
*/
void PORTA_IO_PA0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_IO_PA0_InterruptHandler = interruptHandler;
}

void PORTA_IO_PA0_DefaultInterruptHandler(void)
{
    // add your PORTA_IO_PA0 interrupt custom code
    // or set custom function using PORTA_IO_PA0_SetInterruptHandler()
    *logic = IO_PA0_GetValue();
}
/**
  Allows selecting an interrupt handler for PORTF_IO_PF4 at application runtime
*/
void PORTF_IO_PF4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_IO_PF4_InterruptHandler = interruptHandler;
}

void PORTF_IO_PF4_DefaultInterruptHandler(void)
{
    // add your PORTF_IO_PF4 interrupt custom code
    // or set custom function using PORTF_IO_PF4_SetInterruptHandler()
}
ISR(PORTF_PORT_vect)
{  
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT6_bm)
    {
       PORTF_IO_PF6_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT3_bm)
    {
       PORTF_IO_PF3_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       PORTF_IO_PF2_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       PORTF_IO_PF5_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       PORTF_IO_PF4_InterruptHandler();
    }

    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

ISR(PORTA_PORT_vect)
{  
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       PORTA_IO_PA1_InterruptHandler();
    }
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       PORTA_IO_PA0_InterruptHandler();
    }

    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

