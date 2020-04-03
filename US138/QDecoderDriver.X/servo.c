/*
 * File:   servo.c
 * Author: tblisonb
 *
 * Created on February 25, 2020, 1:38 PM
 */

#include "servo.h"
#include "mcc_generated_files/include/tcb0.h"

void return_neutral(volatile unsigned char* reg, char pin) {
    (*reg) |= (1 << pin); // set pin high to start pulse
    DELAY_microseconds(MIN_PULSE); // delay for min pulse to reset to 0 deg.
    (*reg) &= ~(1 << pin); // set pin low to end pulse
    DELAY_microseconds(CYCLE_TIME - MIN_PULSE); // wait for remaining cycle
}

int rotate_pulse(int degrees, volatile unsigned char* reg, char pin) {
    long length = 0;
    if (degrees <= 180) { // verify input within bounds
        (*reg) |= (1 << pin); // set pin high to start pulse
        // calculate the length of the pulse needed for 'degrees' offset
        length = (((long)(MAX_PULSE - MIN_PULSE)) * degrees) / RANGE_DEGREES;
        DELAY_microseconds(length); // delay for pulse to reach 'degrees' offset
        (*reg) &= ~(1 << pin); // set pin low to end pulse
    }
    return length;
}

void rotate_hold(int degrees, int hold_delay, volatile unsigned char* reg, char pin) {
    long us_remain = hold_delay * 1000; // convert to us
    // call rotate_pulse for as many cycles are within 'hold_delay'
    while (us_remain > 0) {
        int length = rotate_pulse(degrees, reg, pin);
        us_remain -= CYCLE_TIME; // update time remaining
        DELAY_microseconds(CYCLE_TIME - length);
    }
    
}