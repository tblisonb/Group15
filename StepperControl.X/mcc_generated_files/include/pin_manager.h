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

//get/set IO_PD1 aliases
#define IO_PD1_SetHigh() do { PORTD_OUTSET = 0x2; } while(0)
#define IO_PD1_SetLow() do { PORTD_OUTCLR = 0x2; } while(0)
#define IO_PD1_Toggle() do { PORTD_OUTTGL = 0x2; } while(0)
#define IO_PD1_GetValue() (VPORTD.IN & (0x1 << 1))
#define IO_PD1_SetDigitalInput() do { PORTD_DIRCLR = 0x2; } while(0)
#define IO_PD1_SetDigitalOutput() do { PORTD_DIRSET = 0x2; } while(0)
#define IO_PD1_SetPullUp() do { PORTD_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PD1_ResetPullUp() do { PORTD_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PD1_SetInverted() do { PORTD_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PD1_ResetInverted() do { PORTD_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PD1_DisableInterruptOnChange() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PD1_EnableInterruptForBothEdges() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PD1_EnableInterruptForRisingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PD1_EnableInterruptForFallingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PD1_DisableDigitalInputBuffer() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PD1_EnableInterruptForLowLevelSensing() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PC0 aliases
#define IO_PC0_SetHigh() do { PORTC_OUTSET = 0x1; } while(0)
#define IO_PC0_SetLow() do { PORTC_OUTCLR = 0x1; } while(0)
#define IO_PC0_Toggle() do { PORTC_OUTTGL = 0x1; } while(0)
#define IO_PC0_GetValue() (VPORTC.IN & (0x1 << 0))
#define IO_PC0_SetDigitalInput() do { PORTC_DIRCLR = 0x1; } while(0)
#define IO_PC0_SetDigitalOutput() do { PORTC_DIRSET = 0x1; } while(0)
#define IO_PC0_SetPullUp() do { PORTC_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PC0_ResetPullUp() do { PORTC_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PC0_SetInverted() do { PORTC_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PC0_ResetInverted() do { PORTC_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PC0_DisableInterruptOnChange() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PC0_EnableInterruptForBothEdges() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PC0_EnableInterruptForRisingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PC0_EnableInterruptForFallingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PC0_DisableDigitalInputBuffer() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PC0_EnableInterruptForLowLevelSensing() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PD0 aliases
#define IO_PD0_SetHigh() do { PORTD_OUTSET = 0x1; } while(0)
#define IO_PD0_SetLow() do { PORTD_OUTCLR = 0x1; } while(0)
#define IO_PD0_Toggle() do { PORTD_OUTTGL = 0x1; } while(0)
#define IO_PD0_GetValue() (VPORTD.IN & (0x1 << 0))
#define IO_PD0_SetDigitalInput() do { PORTD_DIRCLR = 0x1; } while(0)
#define IO_PD0_SetDigitalOutput() do { PORTD_DIRSET = 0x1; } while(0)
#define IO_PD0_SetPullUp() do { PORTD_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PD0_ResetPullUp() do { PORTD_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PD0_SetInverted() do { PORTD_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PD0_ResetInverted() do { PORTD_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PD0_DisableInterruptOnChange() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PD0_EnableInterruptForBothEdges() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PD0_EnableInterruptForRisingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PD0_EnableInterruptForFallingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PD0_DisableDigitalInputBuffer() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PD0_EnableInterruptForLowLevelSensing() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PD3 aliases
#define IO_PD3_SetHigh() do { PORTD_OUTSET = 0x8; } while(0)
#define IO_PD3_SetLow() do { PORTD_OUTCLR = 0x8; } while(0)
#define IO_PD3_Toggle() do { PORTD_OUTTGL = 0x8; } while(0)
#define IO_PD3_GetValue() (VPORTD.IN & (0x1 << 3))
#define IO_PD3_SetDigitalInput() do { PORTD_DIRCLR = 0x8; } while(0)
#define IO_PD3_SetDigitalOutput() do { PORTD_DIRSET = 0x8; } while(0)
#define IO_PD3_SetPullUp() do { PORTD_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PD3_ResetPullUp() do { PORTD_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PD3_SetInverted() do { PORTD_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PD3_ResetInverted() do { PORTD_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PD3_DisableInterruptOnChange() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PD3_EnableInterruptForBothEdges() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PD3_EnableInterruptForRisingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PD3_EnableInterruptForFallingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PD3_DisableDigitalInputBuffer() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PD3_EnableInterruptForLowLevelSensing() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PD2 aliases
#define IO_PD2_SetHigh() do { PORTD_OUTSET = 0x4; } while(0)
#define IO_PD2_SetLow() do { PORTD_OUTCLR = 0x4; } while(0)
#define IO_PD2_Toggle() do { PORTD_OUTTGL = 0x4; } while(0)
#define IO_PD2_GetValue() (VPORTD.IN & (0x1 << 2))
#define IO_PD2_SetDigitalInput() do { PORTD_DIRCLR = 0x4; } while(0)
#define IO_PD2_SetDigitalOutput() do { PORTD_DIRSET = 0x4; } while(0)
#define IO_PD2_SetPullUp() do { PORTD_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PD2_ResetPullUp() do { PORTD_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PD2_SetInverted() do { PORTD_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PD2_ResetInverted() do { PORTD_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PD2_DisableInterruptOnChange() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PD2_EnableInterruptForBothEdges() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PD2_EnableInterruptForRisingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PD2_EnableInterruptForFallingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PD2_DisableDigitalInputBuffer() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PD2_EnableInterruptForLowLevelSensing() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

void PIN_MANAGER_Initialize();
void PORTD_IO_PD1_DefaultInterruptHandler(void);
void PORTD_IO_PD1_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTC_IO_PC0_DefaultInterruptHandler(void);
void PORTC_IO_PC0_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_IO_PD0_DefaultInterruptHandler(void);
void PORTD_IO_PD0_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_IO_PD3_DefaultInterruptHandler(void);
void PORTD_IO_PD3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_IO_PD2_DefaultInterruptHandler(void);
void PORTD_IO_PD2_SetInterruptHandler(void (* interruptHandler)(void)) ;
#endif /* PINS_H_INCLUDED */
