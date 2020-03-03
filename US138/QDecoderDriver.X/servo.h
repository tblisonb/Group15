/* 
 * File:   servo.h
 * Author: Tanner Lisonbee
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SERVO_H
#define	SERVO_H

#define F_CPU 1000000UL

#include <xc.h> // include processor files - each processor file is guarded.  
#include <util/delay.h>

#define MIN_PULSE     1000  // us for 0 degrees
#define MAX_PULSE     2000  // us for max turn
#define RANGE_DEGREES 180   // max turn in degrees
#define CYCLE_TIME    20000 // total pulse cycle time in us

/**
 * Resets the servo's position to 0 degrees.
 * 
 * @param reg Register assigned to servo output
 * @param pin Pin number in 'reg' for servo output
 */
void return_neutral(volatile unsigned char* reg, char pin);

/**
 * Temporarily rotates the servo to 'degrees' offset from zero.
 * 
 * @param degrees Angular offset from zero in degrees
 * @param reg Register assigned to servo output
 * @param pin Pin number in 'reg' for servo output
 * @return Pulse length for rotation
 */
int rotate_pulse(int degrees, volatile unsigned char* reg, char pin);

/**
 * Rotates and holds at 'degrees' offset from zero.
 * 
 * @param degrees Angular offset from zero in degrees
 * @param hold_delay Time to hold position in ms
 * @param reg Register assigned to servo output
 * @param pin Pin number in 'reg' for servo output
 */
void rotate_hold(int degrees, int hold_delay, volatile unsigned char* reg, char pin);

#endif	/* XC_HEADER_TEMPLATE_H */

