/* 
 * File:   wire.h
 * Author: Tanner Lisonbee
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define EXTRUDER_GEAR_RADIUS 5 // mm
#define ENCODER_NUM_STEPS 20 // steps for one full rotation
#define STEP_RADIANS (62832 / ENCODER_NUM_STEPS) // angular displacement *= 10E-4
#define STEPPER_PORT ((volatile unsigned char*) &PORTB)
#define SERVO_PORT ((volatile unsigned char*) &PORTC)
#define SERVO_BIT 0
#define STRIP_OFFSET_ANGLE 70
#define CUT_OFFSET_ANGLE 90

/*
 * Runs the stepper motor for a single step to extrude wire.
 */
void extrude_min_step();

/*
 * Extrudes 'length' wire.
 * 
 * @param length Length of wire to be extruded in mm
 */
void extrude(int length);

/*
 * Runs the stepper motor for a single step to retract wire.
 */
void retract_min_step();

/*
 * Retracts 'length' wire.
 * 
 * @param length Length of wire to be retracted in mm
 */
void retract(int length);

/*
 * Triggers the servo to score the wire to be stripped.
 */
void strip();

/*
 * Triggers the servo to cut the wire at the current length.
 */
void cut();

#endif	/* XC_HEADER_TEMPLATE_H */

