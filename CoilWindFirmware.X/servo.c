/*
 * File:   servo.c
 * Author: tblisonb
 *
 * Created on February 25, 2020, 1:38 PM
 */

#include "servo.h"
#include "mcc_generated_files/include/tca0.h"

/*
#if TCA0.SINGLE.CTRLA == 0x01
#define DIVSFT 0
#elif TCA0.SINGLE.CTRLA == 0x02
#define DIVSFT 1
#elif TCA0.SINGLE.CTRLA == 0x05
#define DIVSFT 2
#elif TCA0.SINGLE.CTRLA == 0x07
#define DIVSFT 3
#elif TCA0.SINGLE.CTRLA == 0x09
#define DIVSFT 4
#elif TCA0.SINGLE.CTRLA == 0x011
#define DIVSFT 6
#elif TCA0.SINGLE.CTRLA == 0x013
#define DIVSFT 8
#elif TCA0.SINGLE.CTRLA == 0x015
#define DIVSFT 10
#else*/
#define DIVSFT 4 // default
//#endif
#define CMP_PERIOD (F_CPU >> DIVSFT) / (1000000 / CYCLE_TIME)

void init() {
    // set compare value for 20ms pulse length
    TCA0.SINGLE.PERL = (CMP_PERIOD & 0x00FF);
    TCA0.SINGLE.PERH = (CMP_PERIOD & 0xFF00) >> 8;
}

void set_duty_cycle(uint8_t degrees) {
    // calculate the length of the pulse needed for 'degrees' offset
    uint16_t length = (uint16_t)((((long)(MAX_PULSE - MIN_PULSE)) * (long)degrees) / RANGE_DEGREES) + MIN_PULSE;
    uint16_t cmp_pulse = CMP_PERIOD / (CYCLE_TIME / length);
    TCA0.SINGLE.CMP0L = (cmp_pulse & 0x00FF);
    TCA0.SINGLE.CMP0H = (cmp_pulse & 0xFF00) >> 8;
}

void rotate(uint8_t degrees) {
    set_duty_cycle(degrees);
}