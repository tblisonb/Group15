/*
 * File:   wire.c
 * Author: tblisonb
 *
 * Created on February 17, 2020, 2:03 PM
 */

#include <xc.h>
#include "wire.h"
#include "servo.h"
#include "stepper.h"

int steps_from_length(int length) {
    return ((length * 1000) / (EXTRUDER_GEAR_RADIUS * 1000)) / STEP_RADIANS;
}

void extrude_min_step() {
    //cw_step(STEPPER_PORT);
}

void extrude(int length) {
    int steps = steps_from_length(length);
    cw_turn(STEPPER_PORT, steps, 1);
}

void retract_min_step() {
    //cc_step(STEPPER_PORT);
}

void retract(int length) {
    int steps = steps_from_length(length);
    cc_turn(STEPPER_PORT, steps, 1);
}

void strip() {
    //rotate(45);
}

void cut() {
    //rotate_pulse(CUT_OFFSET_ANGLE, SERVO_PORT, SERVO_BIT);
}