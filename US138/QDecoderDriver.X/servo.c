/*
 * File:   servo.c
 * Author: tblisonb
 *
 * Created on February 25, 2020, 1:38 PM
 */

#include "servo.h"
#include "mcc_generated_files/include/pin_manager.h"

void init() {
    //TCB0.CCMPH = 4999;
}

unsigned int rotate_pulse(int degrees, volatile unsigned char* reg, char pin) {
    uint16_t length = 0;
    if (degrees <= 180) { // verify input within bounds
        // calculate the length of the pulse needed for 'degrees' offset
        length = (uint16_t)((((long)(MAX_PULSE - MIN_PULSE)) * (long)degrees) / RANGE_DEGREES) + MIN_PULSE;
        (*reg) |= (1 << pin); // set pin high to start pulse
        DELAY_microseconds(length); // delay for pulse to reach 'degrees' offset
        (*reg) &= ~(1 << pin); // set pin low to end pulse
    }
    return (unsigned int)length;
}

void rotate_hold(int degrees, unsigned long hold_delay, volatile unsigned char* reg, char pin) {
    long us_remain = hold_delay * 1000; // convert to us
    // call rotate_pulse for as many cycles are within 'hold_delay'
    while (us_remain > 0) {
        unsigned int length = rotate_pulse(degrees, reg, pin);
        us_remain -= CYCLE_TIME; // update time remaining
        DELAY_microseconds(CYCLE_TIME - length);
    }
    
}