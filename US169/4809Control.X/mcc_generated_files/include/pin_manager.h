/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
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

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "port.h"

//get/set IO_PB3 aliases
#define IO_PB3_SetHigh() do { PORTB_OUTSET = 0x8; } while(0)
#define IO_PB3_SetLow() do { PORTB_OUTCLR = 0x8; } while(0)
#define IO_PB3_Toggle() do { PORTB_OUTTGL = 0x8; } while(0)
#define IO_PB3_GetValue() (VPORTB.IN & (0x1 << 3))
#define IO_PB3_SetDigitalInput() do { PORTB_DIRCLR = 0x8; } while(0)
#define IO_PB3_SetDigitalOutput() do { PORTB_DIRSET = 0x8; } while(0)
#define IO_PB3_SetPullUp() do { PORTB_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PB3_ResetPullUp() do { PORTB_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PB3_SetInverted() do { PORTB_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PB3_ResetInverted() do { PORTB_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PB3_DisableInterruptOnChange() do { PORTB.PIN3CTRL = (PORTB.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PB3_EnableInterruptForBothEdges() do { PORTB.PIN3CTRL = (PORTB.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PB3_EnableInterruptForRisingEdge() do { PORTB.PIN3CTRL = (PORTB.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PB3_EnableInterruptForFallingEdge() do { PORTB.PIN3CTRL = (PORTB.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PB3_DisableDigitalInputBuffer() do { PORTB.PIN3CTRL = (PORTB.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PB3_EnableInterruptForLowLevelSensing() do { PORTB.PIN3CTRL = (PORTB.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PB2 aliases
#define IO_PB2_SetHigh() do { PORTB_OUTSET = 0x4; } while(0)
#define IO_PB2_SetLow() do { PORTB_OUTCLR = 0x4; } while(0)
#define IO_PB2_Toggle() do { PORTB_OUTTGL = 0x4; } while(0)
#define IO_PB2_GetValue() (VPORTB.IN & (0x1 << 2))
#define IO_PB2_SetDigitalInput() do { PORTB_DIRCLR = 0x4; } while(0)
#define IO_PB2_SetDigitalOutput() do { PORTB_DIRSET = 0x4; } while(0)
#define IO_PB2_SetPullUp() do { PORTB_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PB2_ResetPullUp() do { PORTB_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PB2_SetInverted() do { PORTB_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PB2_ResetInverted() do { PORTB_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PB2_DisableInterruptOnChange() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PB2_EnableInterruptForBothEdges() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PB2_EnableInterruptForRisingEdge() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PB2_EnableInterruptForFallingEdge() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PB2_DisableDigitalInputBuffer() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PB2_EnableInterruptForLowLevelSensing() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA1 aliases
#define PA1_SetHigh() do { PORTA_OUTSET = 0x2; } while(0)
#define PA1_SetLow() do { PORTA_OUTCLR = 0x2; } while(0)
#define PA1_Toggle() do { PORTA_OUTTGL = 0x2; } while(0)
#define PA1_GetValue() (VPORTA.IN & (0x1 << 1))
#define PA1_SetDigitalInput() do { PORTA_DIRCLR = 0x2; } while(0)
#define PA1_SetDigitalOutput() do { PORTA_DIRSET = 0x2; } while(0)
#define PA1_SetPullUp() do { PORTA_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA1_ResetPullUp() do { PORTA_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA1_SetInverted() do { PORTA_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define PA1_ResetInverted() do { PORTA_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA1_DisableInterruptOnChange() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA1_EnableInterruptForBothEdges() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA1_EnableInterruptForRisingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA1_EnableInterruptForFallingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA1_DisableDigitalInputBuffer() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA1_EnableInterruptForLowLevelSensing() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PC3 aliases
#define PC3_SetHigh() do { PORTC_OUTSET = 0x8; } while(0)
#define PC3_SetLow() do { PORTC_OUTCLR = 0x8; } while(0)
#define PC3_Toggle() do { PORTC_OUTTGL = 0x8; } while(0)
#define PC3_GetValue() (VPORTC.IN & (0x1 << 3))
#define PC3_SetDigitalInput() do { PORTC_DIRCLR = 0x8; } while(0)
#define PC3_SetDigitalOutput() do { PORTC_DIRSET = 0x8; } while(0)
#define PC3_SetPullUp() do { PORTC_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PC3_ResetPullUp() do { PORTC_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PC3_SetInverted() do { PORTC_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define PC3_ResetInverted() do { PORTC_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PC3_DisableInterruptOnChange() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PC3_EnableInterruptForBothEdges() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PC3_EnableInterruptForRisingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PC3_EnableInterruptForFallingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PC3_DisableDigitalInputBuffer() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PC3_EnableInterruptForLowLevelSensing() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA3 aliases
#define PA3_SetHigh() do { PORTA_OUTSET = 0x8; } while(0)
#define PA3_SetLow() do { PORTA_OUTCLR = 0x8; } while(0)
#define PA3_Toggle() do { PORTA_OUTTGL = 0x8; } while(0)
#define PA3_GetValue() (VPORTA.IN & (0x1 << 3))
#define PA3_SetDigitalInput() do { PORTA_DIRCLR = 0x8; } while(0)
#define PA3_SetDigitalOutput() do { PORTA_DIRSET = 0x8; } while(0)
#define PA3_SetPullUp() do { PORTA_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA3_ResetPullUp() do { PORTA_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA3_SetInverted() do { PORTA_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define PA3_ResetInverted() do { PORTA_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA3_DisableInterruptOnChange() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA3_EnableInterruptForBothEdges() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA3_EnableInterruptForRisingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA3_EnableInterruptForFallingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA3_DisableDigitalInputBuffer() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA3_EnableInterruptForLowLevelSensing() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PD1 aliases
#define PD1_SetHigh() do { PORTD_OUTSET = 0x2; } while(0)
#define PD1_SetLow() do { PORTD_OUTCLR = 0x2; } while(0)
#define PD1_Toggle() do { PORTD_OUTTGL = 0x2; } while(0)
#define PD1_GetValue() (VPORTD.IN & (0x1 << 1))
#define PD1_SetDigitalInput() do { PORTD_DIRCLR = 0x2; } while(0)
#define PD1_SetDigitalOutput() do { PORTD_DIRSET = 0x2; } while(0)
#define PD1_SetPullUp() do { PORTD_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PD1_ResetPullUp() do { PORTD_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PD1_SetInverted() do { PORTD_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define PD1_ResetInverted() do { PORTD_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PD1_DisableInterruptOnChange() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PD1_EnableInterruptForBothEdges() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PD1_EnableInterruptForRisingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PD1_EnableInterruptForFallingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PD1_DisableDigitalInputBuffer() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PD1_EnableInterruptForLowLevelSensing() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PF3 aliases
#define PF3_SetHigh() do { PORTF_OUTSET = 0x8; } while(0)
#define PF3_SetLow() do { PORTF_OUTCLR = 0x8; } while(0)
#define PF3_Toggle() do { PORTF_OUTTGL = 0x8; } while(0)
#define PF3_GetValue() (VPORTF.IN & (0x1 << 3))
#define PF3_SetDigitalInput() do { PORTF_DIRCLR = 0x8; } while(0)
#define PF3_SetDigitalOutput() do { PORTF_DIRSET = 0x8; } while(0)
#define PF3_SetPullUp() do { PORTF_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PF3_ResetPullUp() do { PORTF_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PF3_SetInverted() do { PORTF_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define PF3_ResetInverted() do { PORTF_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PF3_DisableInterruptOnChange() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PF3_EnableInterruptForBothEdges() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PF3_EnableInterruptForRisingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PF3_EnableInterruptForFallingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PF3_DisableDigitalInputBuffer() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PF3_EnableInterruptForLowLevelSensing() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PD0 aliases
#define PD0_SetHigh() do { PORTD_OUTSET = 0x1; } while(0)
#define PD0_SetLow() do { PORTD_OUTCLR = 0x1; } while(0)
#define PD0_Toggle() do { PORTD_OUTTGL = 0x1; } while(0)
#define PD0_GetValue() (VPORTD.IN & (0x1 << 0))
#define PD0_SetDigitalInput() do { PORTD_DIRCLR = 0x1; } while(0)
#define PD0_SetDigitalOutput() do { PORTD_DIRSET = 0x1; } while(0)
#define PD0_SetPullUp() do { PORTD_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PD0_ResetPullUp() do { PORTD_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PD0_SetInverted() do { PORTD_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define PD0_ResetInverted() do { PORTD_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PD0_DisableInterruptOnChange() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PD0_EnableInterruptForBothEdges() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PD0_EnableInterruptForRisingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PD0_EnableInterruptForFallingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PD0_DisableDigitalInputBuffer() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PD0_EnableInterruptForLowLevelSensing() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PB1 aliases
#define IO_PB1_SetHigh() do { PORTB_OUTSET = 0x2; } while(0)
#define IO_PB1_SetLow() do { PORTB_OUTCLR = 0x2; } while(0)
#define IO_PB1_Toggle() do { PORTB_OUTTGL = 0x2; } while(0)
#define IO_PB1_GetValue() (VPORTB.IN & (0x1 << 1))
#define IO_PB1_SetDigitalInput() do { PORTB_DIRCLR = 0x2; } while(0)
#define IO_PB1_SetDigitalOutput() do { PORTB_DIRSET = 0x2; } while(0)
#define IO_PB1_SetPullUp() do { PORTB_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PB1_ResetPullUp() do { PORTB_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PB1_SetInverted() do { PORTB_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PB1_ResetInverted() do { PORTB_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PB1_DisableInterruptOnChange() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PB1_EnableInterruptForBothEdges() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PB1_EnableInterruptForRisingEdge() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PB1_EnableInterruptForFallingEdge() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PB1_DisableDigitalInputBuffer() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PB1_EnableInterruptForLowLevelSensing() do { PORTB.PIN1CTRL = (PORTB.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA0 aliases
#define PA0_SetHigh() do { PORTA_OUTSET = 0x1; } while(0)
#define PA0_SetLow() do { PORTA_OUTCLR = 0x1; } while(0)
#define PA0_Toggle() do { PORTA_OUTTGL = 0x1; } while(0)
#define PA0_GetValue() (VPORTA.IN & (0x1 << 0))
#define PA0_SetDigitalInput() do { PORTA_DIRCLR = 0x1; } while(0)
#define PA0_SetDigitalOutput() do { PORTA_DIRSET = 0x1; } while(0)
#define PA0_SetPullUp() do { PORTA_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA0_ResetPullUp() do { PORTA_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA0_SetInverted() do { PORTA_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define PA0_ResetInverted() do { PORTA_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA0_DisableInterruptOnChange() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA0_EnableInterruptForBothEdges() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA0_EnableInterruptForRisingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA0_EnableInterruptForFallingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA0_DisableDigitalInputBuffer() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA0_EnableInterruptForLowLevelSensing() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PD3 aliases
#define PD3_SetHigh() do { PORTD_OUTSET = 0x8; } while(0)
#define PD3_SetLow() do { PORTD_OUTCLR = 0x8; } while(0)
#define PD3_Toggle() do { PORTD_OUTTGL = 0x8; } while(0)
#define PD3_GetValue() (VPORTD.IN & (0x1 << 3))
#define PD3_SetDigitalInput() do { PORTD_DIRCLR = 0x8; } while(0)
#define PD3_SetDigitalOutput() do { PORTD_DIRSET = 0x8; } while(0)
#define PD3_SetPullUp() do { PORTD_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PD3_ResetPullUp() do { PORTD_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PD3_SetInverted() do { PORTD_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define PD3_ResetInverted() do { PORTD_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PD3_DisableInterruptOnChange() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PD3_EnableInterruptForBothEdges() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PD3_EnableInterruptForRisingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PD3_EnableInterruptForFallingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PD3_DisableDigitalInputBuffer() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PD3_EnableInterruptForLowLevelSensing() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PB0 aliases
#define IO_PB0_SetHigh() do { PORTB_OUTSET = 0x1; } while(0)
#define IO_PB0_SetLow() do { PORTB_OUTCLR = 0x1; } while(0)
#define IO_PB0_Toggle() do { PORTB_OUTTGL = 0x1; } while(0)
#define IO_PB0_GetValue() (VPORTB.IN & (0x1 << 0))
#define IO_PB0_SetDigitalInput() do { PORTB_DIRCLR = 0x1; } while(0)
#define IO_PB0_SetDigitalOutput() do { PORTB_DIRSET = 0x1; } while(0)
#define IO_PB0_SetPullUp() do { PORTB_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PB0_ResetPullUp() do { PORTB_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PB0_SetInverted() do { PORTB_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PB0_ResetInverted() do { PORTB_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PB0_DisableInterruptOnChange() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PB0_EnableInterruptForBothEdges() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PB0_EnableInterruptForRisingEdge() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PB0_EnableInterruptForFallingEdge() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PB0_DisableDigitalInputBuffer() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PB0_EnableInterruptForLowLevelSensing() do { PORTB.PIN0CTRL = (PORTB.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

void PIN_MANAGER_Initialize();
void PORTB_IO_PB3_DefaultInterruptHandler(void);
void PORTB_IO_PB3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTB_IO_PB2_DefaultInterruptHandler(void);
void PORTB_IO_PB2_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA1_DefaultInterruptHandler(void);
void PORTA_PA1_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTC_PC3_DefaultInterruptHandler(void);
void PORTC_PC3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA3_DefaultInterruptHandler(void);
void PORTA_PA3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_PD1_DefaultInterruptHandler(void);
void PORTD_PD1_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_PF3_DefaultInterruptHandler(void);
void PORTF_PF3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_PD0_DefaultInterruptHandler(void);
void PORTD_PD0_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTB_IO_PB1_DefaultInterruptHandler(void);
void PORTB_IO_PB1_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA0_DefaultInterruptHandler(void);
void PORTA_PA0_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_PD3_DefaultInterruptHandler(void);
void PORTD_PD3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTB_IO_PB0_DefaultInterruptHandler(void);
void PORTB_IO_PB0_SetInterruptHandler(void (* interruptHandler)(void)) ;
#endif /* PINS_H_INCLUDED */
