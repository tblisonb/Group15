/* 
 * File:   servo.h
 * Author: Tanner Lisonbee
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SERVO_H
#define	SERVO_H

#include "mcc_generated_files/delay.h"

#define MIN_PULSE     336   // us for 0 degrees
#define MAX_PULSE     2200  // us for max turn
#define RANGE_DEGREES 270   // max turn in degrees
#define CYCLE_TIME    19797 // total pulse cycle time in us

void init();

/**
 * Temporarily rotates the servo to 'degrees' offset from zero.
 * 
 * @param degrees Angular offset from zero in degrees
 * @param reg Register assigned to servo output
 * @param pin Pin number in 'reg' for servo output
 * @return Pulse length for rotation
 */
unsigned int rotate_pulse(int degrees, volatile unsigned char* reg, char pin);

/**
 * Rotates and holds at 'degrees' offset from zero.
 * 
 * @param degrees Angular offset from zero in degrees
 * @param hold_delay Time to hold position in ms
 * @param reg Register assigned to servo output
 * @param pin Pin number in 'reg' for servo output
 */
void rotate_hold(int degrees, unsigned long hold_delay, volatile unsigned char* reg, char pin);

#endif	/* XC_HEADER_TEMPLATE_H */

