/* 
 * File:   stepper.h
 * Author: Tanner Lisonbee
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_STEPPER_H
#define	XC_STEPPER_H

#include <avr/io.h>
#include <stdint.h>
#include "mcc_generated_files/delay.h"

#define STATE1 0xA
#define STATE2 0x6
#define STATE3 0x5
#define STATE4 0x9

unsigned int mm_to_steps(unsigned int mm);

/*
 * Reads the register assigned to the stepper motor output and changes the state
 * such that a single clockwise step occurs on the stepper motor.
 * 
 * @param reg Output register assigned for the stepper motor control
 */
unsigned char cw_step(volatile unsigned char* reg, volatile unsigned char prev_state);

/*
 * Reads the register assigned to the stepper motor output and changes the state
 * such that a single clockwise step occurs on the stepper motor.
 * 
 * @param reg Output register assigned for the stepper motor control
 */
unsigned char cc_step(volatile unsigned char* reg, volatile unsigned char prev_state);

/*
 * Adjusts the state of the stepper motor over time to turn the output shaft in
 * the clockwise direction for a specified number of steps.
 * 
 * @param reg Output register assigned for the stepper motor control
 * @param num_steps Number of steps to turn the stepper motor
 * @param delay Delay between state changes (for speed control) in ms
 */
void cw_turn(volatile unsigned char* reg, int num_steps, int delay);

/*
 * Adjusts the state of the stepper motor over time to turn the output shaft in
 * the counterclockwise direction for a specified number of steps.
 * 
 * @param reg Output register assigned for the stepper motor control
 * @param num_steps Number of steps to turn the stepper motor
 * @param delay Delay between state changes (for speed control) in ms
 */
void cc_turn(volatile unsigned char* reg, int num_steps, int delay);

#endif	/* XC_HEADER_TEMPLATE_H */

