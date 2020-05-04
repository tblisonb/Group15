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


#include "../include/ccl.h"

/**
 * \brief Initialize CCL peripheral
 * \return Return value 0 if success
 */
int8_t CCL_Initialize()
{

    //INTMODE3 INTDISABLE; INTMODE2 INTDISABLE; INTMODE1 INTDISABLE; INTMODE0 INTDISABLE; 
	CCL.INTCTRL0 = 0x00;

    //INT 0; 
	CCL.INTFLAGS = 0x00;

    //INSEL1 IO; INSEL0 MASK; 
	CCL.LUT0CTRLB = 0x50;

    //INSEL2 IO; 
	CCL.LUT0CTRLC = 0x05;

    //INSEL1 MASK; INSEL0 MASK; 
	CCL.LUT1CTRLB = 0x00;
	
    //INSEL2 MASK; 
	CCL.LUT1CTRLC = 0x00;

    //INSEL1 IO; INSEL0 IO; 
	CCL.LUT2CTRLB = 0x55;
	
    //INSEL2 MASK; 
	CCL.LUT2CTRLC = 0x00;

    //INSEL1 MASK; INSEL0 MASK; 
	CCL.LUT3CTRLB = 0x00;
	
    //INSEL2 MASK; 
	CCL.LUT3CTRLC = 0x00;

    //SEQSEL0 DISABLE; 
	CCL.SEQCTRL0 = 0x00;

    //SEQSEL1 DISABLE; 
	CCL.SEQCTRL1 = 0x00;

    //Truth 0
	CCL.TRUTH0 = 0x40;

    //Truth 1
	CCL.TRUTH1 = 0x00;

    //Truth 2
	CCL.TRUTH2 = 0x08;

    //Truth 3
	CCL.TRUTH3 = 0x00;

    //EDGEDET EN; OUTEN enabled; FILTSEL DISABLE; CLKSRC CLKPER; ENABLE enabled; 
	CCL.LUT0CTRLA = 0xC1;

    //EDGEDET DIS; OUTEN disabled; FILTSEL DISABLE; CLKSRC CLKPER; ENABLE disabled; 
	CCL.LUT1CTRLA = 0x00;

    //EDGEDET DIS; OUTEN enabled; FILTSEL DISABLE; CLKSRC CLKPER; ENABLE enabled; 
	CCL.LUT2CTRLA = 0x41;

    //EDGEDET DIS; OUTEN enabled; FILTSEL DISABLE; CLKSRC CLKPER; ENABLE disabled; 
	CCL.LUT3CTRLA = 0x40;

    //RUNSTDBY disabled; ENABLE enabled; 
	CCL.CTRLA = 0x01;

	return 0;
}

ISR(CCL_CCL_vect)
{
    /*
    * Insert your CCL interrupt handling code
    *
    * Interrupt flag can be cleared by writing 1 to its bit location
    * in the INTFLAGS register
    */
}

