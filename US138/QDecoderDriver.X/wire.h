/* 
 * File:   wire.h
 * Author: Tanner Lisonbee
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef WIRE_TEMPLATE_H
#define	WIRE_TEMPLATE_H

#include "servo.h"
#include "stepper.h"
#include "RN487x.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/include/pin_manager.h"

#define EXTRUDER_GEAR_RADIUS 5 // mm
#define ENCODER_NUM_STEPS 20 // steps for one full rotation
#define STEP_RADIANS (62832 / ENCODER_NUM_STEPS) // angular displacement *= 10E-4
#define STEPPER_PORT ((volatile unsigned char*) &PORTE.OUT)
#define SERVO_PORT ((volatile unsigned char*) &PORTA.OUT)
#define SERVO_BIT 2
#define STRIP_OFFSET_ANGLE 70
#define CUT_OFFSET_ANGLE 90
#define STEPPER_DELAY 25

/*
 * Initializes system.
 */
void init_wire();

/*
 * Checks and reads data from BLE module.
 */
void read_data(volatile uint8_t* buffer);

/*
 * Extrudes 'length' wire.
 * 
 * @param length Length of wire to be extruded in mm
 */
void extrude(int length);

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

#endif	/* WIRE_TEMPLATE_H */

