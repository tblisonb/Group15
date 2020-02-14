/*
 * File:   actuator.c
 * Author: tblisonb
 *
 * Created on February 6, 2020, 3:15 PM
 */


#include <xc.h>
#include "actuator.h"

void actuator_toggle(volatile uint8_t* reg, int bit_num) {
    (*reg) ^= (1 << bit_num); // flip output bit on 'reg'
}

void actuator_extend(volatile uint8_t* reg, int bit_num) {
    (*reg) |= (1 << bit_num); // turn output bit high on 'reg'
}

void actuator_release(volatile uint8_t* reg, int bit_num) {
    (*reg) &= (1 << bit_num); // turn output bit low on 'reg'
}

void actuator_pulse(volatile uint8_t* reg, int bit_num, int length) {
    (*reg) |= (1 << bit_num); // turn output high
    int i;
    // delay (for loop since _delay_ms cannot take variable input)
    for (i = 0; i < length; i++) {
        _delay_ms(100);
    }
    (*reg) &= (1 << bit_num); // turn output low
}

void actuator_pulse_inv(volatile uint8_t* reg, int bit_num, int length) {
    (*reg) &= (1 << bit_num); // turn output low
    int i;
    // delay (for loop since _delay_ms cannot take variable input)
    for (i = 0; i < length; i++) {
        _delay_ms(100);
    }
    (*reg) |= (1 << bit_num); // turn output high
}