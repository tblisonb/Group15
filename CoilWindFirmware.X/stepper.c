#include "stepper.h"

#define STEPS_PER_ROT 200000
#define GEAR_CIRCUMFERENCE 34000 // um

unsigned int mm_to_steps(unsigned int mm) {
    return STEPS_PER_ROT / (GEAR_CIRCUMFERENCE / mm);
}

unsigned char cw_step(volatile unsigned char* reg, volatile unsigned char prev_state) {
    // check state of reg, and increase state value to step clockwise
    switch(prev_state) {
    case STATE1:
        (*reg) = STATE2;
        return STATE2;
    case STATE2:
        (*reg) = STATE3;
        return STATE3;
    case STATE3:
        (*reg) = STATE4;
        return STATE4;
    case STATE4:
        (*reg) = STATE1;
        return STATE1;
    }
    return 0;
}

unsigned char cc_step(volatile unsigned char* reg, volatile unsigned char prev_state) {
    // check state of reg, and decrease state value to step counterclockwise
    switch(prev_state) {
    case STATE1:
        (*reg) = STATE4;
        return STATE4;
    case STATE2:
        (*reg) = STATE1;
        return STATE1;
    case STATE3:
        (*reg) = STATE2;
        return STATE2;
    case STATE4:
        (*reg) = STATE3;
        return STATE3;
    }
    return 0;
}

void cw_turn(volatile unsigned char* reg, int num_steps, int delay) {
    static volatile unsigned char state = STATE1;
    int i;
    // step 'num_steps' clockwise with 'delay' ms between steps
    for (i = 0; i < num_steps; i++) {
        state = cw_step(reg, state);
        DELAY_milliseconds(delay);
    }
}

void cc_turn(volatile unsigned char* reg, int num_steps, int delay) {
    static volatile unsigned char state = STATE1;
    int i;
    // step 'num_steps' counterclockwise with 'delay' ms between steps
    for (i = 0; i < num_steps; i++) {
        state = cc_step(reg, state);
        DELAY_milliseconds(delay);
    }
}