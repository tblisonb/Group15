/* 
 * File:   servo.h
 * Author: Tanner Lisonbee
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SERVO_H
#define	SERVO_H

#include "mcc_generated_files/mcc.h"

#define MIN_PULSE     400    // us for 0 degrees
#define MAX_PULSE     1000   // us for max turn
#define RANGE_DEGREES 90     // max turn in degrees
#define CYCLE_TIME    20000  // total pulse cycle time in us

void init();

/**
 * Rotates and holds at 'degrees' offset from zero.
 * 
 * @param degrees Angular offset from zero in degrees
 */
void rotate(uint8_t degrees);

#endif	/* XC_HEADER_TEMPLATE_H */

