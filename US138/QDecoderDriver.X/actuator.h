/* 
 * File:   actuator.h
 * Author: Tanner Lisonbee
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_ACTUATOR_H
#define	XC_ACTUATOR_H

#include <avr/io.h>
#include <stdint.h>
#include "mcc_generated_files/delay.h" 

/*
 * Reads the state of the actuator bit (given by 'reg' and 'bit_num' and inverts
 * the measured state. If the actuator is extended, then it will release, and 
 * vice versa.
 * 
 * @param reg Register assigned to the actuator output
 * @param bit_num Bit number in the IO register assigned to output
 */
void actuator_toggle(volatile uint8_t* reg, int bit_num);

/*
 * Updates the state of the actuator control bit to be high, thus providing 
 * power to the actuator and extending the output shaft.
 * 
 * @param reg Register assigned to the actuator output
 * @param bit_num Bit number in the IO register assigned to output
 */
void actuator_extend(volatile uint8_t* reg, int bit_num);

/*
 * Updates the state of the actuator control bit to be low, thus removing power
 * from the actuator and retracting the output shaft.
 * 
 * @param reg Register assigned to the actuator output
 * @param bit_num Bit number in the IO register assigned to output
 */
void actuator_release(volatile uint8_t* reg, int bit_num);

/*
 * Sets the output bit for the actuator to high for a specified amount of time
 * before turning it low again.
 * 
 * @param reg Register assigned to the actuator output
 * @param bit_num Bit number in the IO register assigned to output
 * @param length Length in 1/10 seconds that the pulse should hold
 */
void actuator_pulse(volatile uint8_t* reg, int bit_num, int length);

/*
 * Sets the output bit for the actuator to low for a specified amount of time
 * before turning it high again.
 * 
 * @param reg Register assigned to the actuator output
 * @param bit_num Bit number in the IO register assigned to output
 * @param length Length in 1/10 seconds that the pulse should hold
 */
void actuator_pulse_inv(volatile uint8_t* reg, int bit_num, int length);

#endif	/* XC_HEADER_TEMPLATE_H */

