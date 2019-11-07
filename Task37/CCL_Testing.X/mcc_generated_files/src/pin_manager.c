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
static void (*PORTA_PA1_InterruptHandler)(void);
static void (*PORTF_PF6_InterruptHandler)(void);
static void (*PORTC_PC6_InterruptHandler)(void);
static void (*PORTA_PA6_InterruptHandler)(void);
static void (*PORTE_IO_PE0_InterruptHandler)(void);
static void (*PORTF_IO_PF3_InterruptHandler)(void);
static void (*PORTC_PC0_InterruptHandler)(void);
static void (*PORTE_IO_PE1_InterruptHandler)(void);
static void (*PORTA_PA0_InterruptHandler)(void);
static void (*PORTD_PD3_InterruptHandler)(void);
static void (*PORTF_IO_PF4_InterruptHandler)(void);
static void (*PORTC_PC1_InterruptHandler)(void);

void PORT_Initialize(void);

void PIN_MANAGER_Initialize()
{
    PORT_Initialize();

    /* DIR Registers Initialization */
    PORTA.DIR = 0x40;
    PORTB.DIR = 0x00;
    PORTC.DIR = 0x40;
    PORTD.DIR = 0x08;
    PORTE.DIR = 0x00;
    PORTF.DIR = 0x58;

    /* OUT Registers Initialization */
    PORTA.OUT = 0x00;
    PORTB.OUT = 0x00;
    PORTC.OUT = 0x00;
    PORTD.OUT = 0x00;
    PORTE.OUT = 0x00;
    PORTF.OUT = 0x00;

    /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x00;
    PORTA.PIN1CTRL = 0x00;
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
    PORTF.PIN2CTRL = 0x00;
    PORTF.PIN3CTRL = 0x00;
    PORTF.PIN4CTRL = 0x00;
    PORTF.PIN5CTRL = 0x00;
    PORTF.PIN6CTRL = 0x00;
    PORTF.PIN7CTRL = 0x00;

    /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0B;
    PORTMUX.EVSYSROUTEA = 0x00;
    PORTMUX.TCAROUTEA = 0x00;
    PORTMUX.TCBROUTEA = 0x00;
    PORTMUX.TWISPIROUTEA = 0x00;
    PORTMUX.USARTROUTEA = 0x00;

    // register default ISC callback functions at runtime; use these methods to register a custom function
    PORTA_PA1_SetInterruptHandler(PORTA_PA1_DefaultInterruptHandler);
    PORTF_PF6_SetInterruptHandler(PORTF_PF6_DefaultInterruptHandler);
    PORTC_PC6_SetInterruptHandler(PORTC_PC6_DefaultInterruptHandler);
    PORTA_PA6_SetInterruptHandler(PORTA_PA6_DefaultInterruptHandler);
    PORTE_IO_PE0_SetInterruptHandler(PORTE_IO_PE0_DefaultInterruptHandler);
    PORTF_IO_PF3_SetInterruptHandler(PORTF_IO_PF3_DefaultInterruptHandler);
    PORTC_PC0_SetInterruptHandler(PORTC_PC0_DefaultInterruptHandler);
    PORTE_IO_PE1_SetInterruptHandler(PORTE_IO_PE1_DefaultInterruptHandler);
    PORTA_PA0_SetInterruptHandler(PORTA_PA0_DefaultInterruptHandler);
    PORTD_PD3_SetInterruptHandler(PORTD_PD3_DefaultInterruptHandler);
    PORTF_IO_PF4_SetInterruptHandler(PORTF_IO_PF4_DefaultInterruptHandler);
    PORTC_PC1_SetInterruptHandler(PORTC_PC1_DefaultInterruptHandler);
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
  Allows selecting an interrupt handler for PORTA_PA1 at application runtime
*/
void PORTA_PA1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA1_InterruptHandler = interruptHandler;
}

void PORTA_PA1_DefaultInterruptHandler(void)
{
    // add your PORTA_PA1 interrupt custom code
    // or set custom function using PORTA_PA1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_PF6 at application runtime
*/
void PORTF_PF6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_PF6_InterruptHandler = interruptHandler;
}

void PORTF_PF6_DefaultInterruptHandler(void)
{
    // add your PORTF_PF6 interrupt custom code
    // or set custom function using PORTF_PF6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTC_PC6 at application runtime
*/
void PORTC_PC6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_PC6_InterruptHandler = interruptHandler;
}

void PORTC_PC6_DefaultInterruptHandler(void)
{
    // add your PORTC_PC6 interrupt custom code
    // or set custom function using PORTC_PC6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA6 at application runtime
*/
void PORTA_PA6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA6_InterruptHandler = interruptHandler;
}

void PORTA_PA6_DefaultInterruptHandler(void)
{
    // add your PORTA_PA6 interrupt custom code
    // or set custom function using PORTA_PA6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTE_IO_PE0 at application runtime
*/
void PORTE_IO_PE0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTE_IO_PE0_InterruptHandler = interruptHandler;
}

void PORTE_IO_PE0_DefaultInterruptHandler(void)
{
    // add your PORTE_IO_PE0 interrupt custom code
    // or set custom function using PORTE_IO_PE0_SetInterruptHandler()
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
  Allows selecting an interrupt handler for PORTC_PC0 at application runtime
*/
void PORTC_PC0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_PC0_InterruptHandler = interruptHandler;
}

void PORTC_PC0_DefaultInterruptHandler(void)
{
    // add your PORTC_PC0 interrupt custom code
    // or set custom function using PORTC_PC0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTE_IO_PE1 at application runtime
*/
void PORTE_IO_PE1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTE_IO_PE1_InterruptHandler = interruptHandler;
}

void PORTE_IO_PE1_DefaultInterruptHandler(void)
{
    // add your PORTE_IO_PE1 interrupt custom code
    // or set custom function using PORTE_IO_PE1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA0 at application runtime
*/
void PORTA_PA0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA0_InterruptHandler = interruptHandler;
}

void PORTA_PA0_DefaultInterruptHandler(void)
{
    // add your PORTA_PA0 interrupt custom code
    // or set custom function using PORTA_PA0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTD_PD3 at application runtime
*/
void PORTD_PD3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_PD3_InterruptHandler = interruptHandler;
}

void PORTD_PD3_DefaultInterruptHandler(void)
{
    // add your PORTD_PD3 interrupt custom code
    // or set custom function using PORTD_PD3_SetInterruptHandler()
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
/**
  Allows selecting an interrupt handler for PORTC_PC1 at application runtime
*/
void PORTC_PC1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_PC1_InterruptHandler = interruptHandler;
}

void PORTC_PC1_DefaultInterruptHandler(void)
{
    // add your PORTC_PC1 interrupt custom code
    // or set custom function using PORTC_PC1_SetInterruptHandler()
}
