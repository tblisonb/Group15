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
#include <stdio.h>
static void (*PORTF_IO_PF6_InterruptHandler)(void);
static void (*PORTA_PA4_InterruptHandler)(void);
static void (*PORTA_PA5_InterruptHandler)(void);
static void (*PORTE_IO_PE0_InterruptHandler)(void);
static void (*PORTF_IO_PF3_InterruptHandler)(void);
static void (*PORTE_IO_PE1_InterruptHandler)(void);
static void (*PORTF_IO_PF5_InterruptHandler)(void);
static void (*PORTF_IO_PF4_InterruptHandler)(void);

unsigned char oldA = 0; //get the initial value of clkPin
unsigned char oldB = 0; //get the initial value of dtPin
void PORT_Initialize(void);

void PIN_MANAGER_Initialize()
{
    PORT_Initialize();

    /* DIR Registers Initialization */
    PORTA.DIR = 0x10;
    PORTB.DIR = 0x00;
    PORTC.DIR = 0x00;
    PORTD.DIR = 0x00;
    PORTE.DIR = 0x00;
    PORTF.DIR = 0x18;

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
    PORTE.PIN0CTRL = 0x01;
    PORTE.PIN1CTRL = 0x01;
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
    PORTF.PIN6CTRL = 0x0B;
    PORTF.PIN7CTRL = 0x00;

    /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x00;
    PORTMUX.EVSYSROUTEA = 0x00;
    PORTMUX.TCAROUTEA = 0x00;
    PORTMUX.TCBROUTEA = 0x00;
    PORTMUX.TWISPIROUTEA = 0x00;
    PORTMUX.USARTROUTEA = 0x01;

    // register default ISC callback functions at runtime; use these methods to register a custom function
    PORTF_IO_PF6_SetInterruptHandler(PORTF_IO_PF6_DefaultInterruptHandler);
    PORTA_PA4_SetInterruptHandler(PORTA_PA4_DefaultInterruptHandler);
    PORTA_PA5_SetInterruptHandler(PORTA_PA5_DefaultInterruptHandler);
    PORTE_IO_PE0_SetInterruptHandler(PORTE_IO_PE0_DefaultInterruptHandler);
    PORTF_IO_PF3_SetInterruptHandler(PORTF_IO_PF3_DefaultInterruptHandler);
    PORTE_IO_PE1_SetInterruptHandler(PORTE_IO_PE1_DefaultInterruptHandler);
    PORTF_IO_PF5_SetInterruptHandler(PORTF_IO_PF5_DefaultInterruptHandler);
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
  Allows selecting an interrupt handler for PORTA_PA4 at application runtime
*/
void PORTA_PA4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA4_InterruptHandler = interruptHandler;
}

void PORTA_PA4_DefaultInterruptHandler(void)
{
    // add your PORTA_PA4 interrupt custom code
    // or set custom function using PORTA_PA4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA5 at application runtime
*/
void PORTA_PA5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA5_InterruptHandler = interruptHandler;
}

void PORTA_PA5_DefaultInterruptHandler(void)
{
    // add your PORTA_PA5 interrupt custom code
    // or set custom function using PORTA_PA5_SetInterruptHandler()
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
    unsigned char newA = IO_PE0_GetValue();//read the value of clkPin to newA
    unsigned char newB = IO_PE1_GetValue() >> 1;//read the value of dtPin to newB
    //increment the state or decrement the state based on result, 
    //state can never be negative or greater then 7
    unsigned char state = oldA + (oldB << 1) + (newA << 2) + (newB << 3);
    printf(state);
    //Sense falling edge of clkPin
    if (oldA == 0 && newA == 1) {
        if (oldB == newB && oldB == 0) {
            //printf(state);
        } else if (oldB == newB && oldB == 1) {
            //printf(state);
        }
    }
    if (oldA == 1 && newA == 0) {
        if (oldB == newB && oldB == 1) {
            //printf(state);
        } else if (oldB == newB && oldB == 0) {
            //printf(state);
        }
    }
    state = state << 1;
    //store the new state of clkPin and dtPin for the next cycle through
    oldA = newA;
    oldB = newB;
    //display the state to the connected lights
    VPORTF.OUT = state;
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
  Allows selecting an interrupt handler for PORTE_IO_PE1 at application runtime
*/
void PORTE_IO_PE1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTE_IO_PE1_InterruptHandler = interruptHandler;
}

void PORTE_IO_PE1_DefaultInterruptHandler(void)
{
    unsigned char newA = IO_PE0_GetValue();//read the value of clkPin to newA
    unsigned char newB = IO_PE1_GetValue() >> 1;//read the value of dtPin to newB
    //increment the state or decrement the state based on result, 
    //state can never be negative or greater then 7
    unsigned char state = oldA + (oldB << 1) + (newA << 2) + (newB << 3);
    printf(state);
    //Sense falling edge of clkPin
    if (oldA == 0 && newA == 1) {
        if (oldB == newB && oldB == 0) {
            //printf(state);
        } else if (oldB == newB && oldB == 1) {
            //printf(state);
        }
    }
    if (oldA == 1 && newA == 0) {
        if (oldB == newB && oldB == 1) {
            //printf(state);
        } else if (oldB == newB && oldB == 0) {
            //printf(state);
        }
    }
    state = state << 1;
    //store the new state of clkPin and dtPin for the next cycle through
    oldA = newA;
    oldB = newB;
    //display the state to the connected lights
    VPORTF.OUT = state;
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
ISR(PORTE_PORT_vect)
{  
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTE.INTFLAGS & PORT_INT0_bm)
    {
       PORTE_IO_PE0_InterruptHandler();
    }
    if(VPORTE.INTFLAGS & PORT_INT1_bm)
    {
       PORTE_IO_PE1_InterruptHandler();
    }

    /* Clear interrupt flags */
    VPORTE.INTFLAGS = 0xff;
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

