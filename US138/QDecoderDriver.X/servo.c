/*
 * File:   servo.c
 * Author: tblisonb
 *
 * Created on February 25, 2020, 1:38 PM
 */

#include "servo.h"

// needed for delays without known delay amount
static inline void variable_delay_us(int delay) {
    while (delay--) {
        _delay_us(1);
    }
}

void return_neutral(volatile char* reg, char pin) {
    (*reg) |= (1 << pin); // set pin high to start pulse
    _delay_us(MIN_PULSE); // delay for min pulse to reset to 0 deg.
    (*reg) &= ~(1 << pin); // set pin low to end pulse
    _delay_us(CYCLE_TIME - MIN_PULSE); // wait for remaining cycle
}

int rotate_pulse(int degrees, volatile char* reg, char pin) {
    long length = 0;
    if (degrees <= 180) { // verify input within bounds
        (*reg) |= (1 << pin); // set pin high to start pulse
        // calculate the length of the pulse needed for 'degrees' offset
        length = (((long)(MAX_PULSE - MIN_PULSE)) * degrees) / RANGE_DEGREES;
        variable_delay_us(length); // delay for pulse to reach 'degrees' offset
        (*reg) &= ~(1 << pin); // set pin low to end pulse
    }
    return length;
}

void rotate_hold(int degrees, int hold_delay, volatile char* reg, char pin) {
    long us_remain = hold_delay * 1000; // convert to us
    // call rotate_pulse for as many cycles are within 'hold_delay'
    while (us_remain > 0) {
        int length = rotate_pulse(degrees, reg, pin);
        us_remain -= CYCLE_TIME; // update time remaining
        variable_delay_us(CYCLE_TIME - length);
    }
}