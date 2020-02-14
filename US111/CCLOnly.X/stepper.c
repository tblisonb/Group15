#include "stepper.h"

void cw_step(volatile uint8_t* reg) {
    // check state of reg, and increase state value to step clockwise
    if ((*reg) == STATE1)
        (*reg) = STATE2;
    else if ((*reg) == STATE2)
        (*reg) = STATE3;
    else if ((*reg) == STATE3)
        (*reg) = STATE4;
    else if ((*reg) == STATE4)
        (*reg) = STATE1;
}

void cc_step(volatile uint8_t* reg) {
    // check state of reg, and decrease state value to step counterclockwise
    if ((*reg) == STATE4)
        (*reg) = STATE3;
    else if ((*reg) == STATE3)
        (*reg) = STATE2;
    else if ((*reg) == STATE2)
        (*reg) = STATE1;
    else if ((*reg) == STATE1)
        (*reg) = STATE4;
}

void cw_turn(volatile uint8_t* reg, int num_steps, int delay) {
    int i, j;
    // step 'num_steps' clockwise with 'delay' ms between steps
    for (i = 0; i < num_steps; i++) {
        cw_step(reg);
        for (j = 0; j < delay; j++) {
            _delay_ms(100);
        }
    }
}

void cc_turn(volatile uint8_t* reg, int num_steps, int delay) {
    int i, j;
    // step 'num_steps' counterclockwise with 'delay' ms between steps
    for (i = 0; i < num_steps; i++) {
        cw_step(reg);
        for (j = 0; j < delay; j++) {
            _delay_ms(100);
        }
    }
}