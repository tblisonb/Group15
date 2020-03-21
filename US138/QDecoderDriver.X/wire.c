/*
 * File:   wire.c
 * Author: tblisonb
 *
 * Created on February 17, 2020, 2:03 PM
 */

#include "wire.h"

// private helper function
int steps_from_length(int length) {
    return ((length * 1000) / (EXTRUDER_GEAR_RADIUS * 1000)) / STEP_RADIANS;
}

void led_blink(int num_times) {
    for (int i = 0; i < num_times; i++) {
        IO_PF5_SetHigh();
        DELAY_milliseconds(200);
        IO_PF5_SetLow();
        DELAY_milliseconds(200);
    }
    DELAY_milliseconds(800);
}

void init_wire() {
    DELAY_milliseconds(RN487X_STARTUP_DELAY);
    
    RN487X_Init();              // initialize BLE HW module
    DELAY_milliseconds(200);    // allow module to process commands
    RN487X_EnterCmdMode();      // enter command mode
    DELAY_milliseconds(200);    // processing time
    uint8_t cmd_buf[16];        // command buffer
    
    // command to set the name of the device as "Coil_Wind"
    cmd_buf[0] = 'S';
    cmd_buf[1] = '-';
    cmd_buf[2] = ',';
    cmd_buf[3] = 'C';
    cmd_buf[4] = 'o';
    cmd_buf[5] = 'i';
    cmd_buf[6] = 'l';
    cmd_buf[7] = '_';
    cmd_buf[8] = 'W';
    cmd_buf[9] = 'i';
    cmd_buf[10] = 'n';
    cmd_buf[11] = 'd';
    cmd_buf[12] = '\n';
    cmd_buf[13] = '\r';
    
    RN487X_SendCmd(cmd_buf, 14);    // send the command to the BLE module
    DELAY_milliseconds(200);        // processing time
    
    // command to enable "Transparent UART" service
    cmd_buf[0] = 'S';
    cmd_buf[1] = 'S';
    cmd_buf[2] = ',';
    cmd_buf[3] = 'C';
    cmd_buf[4] = 'O';
    cmd_buf[5] = '\n';
    cmd_buf[6] = '\r';
    
    RN487X_SendCmd(cmd_buf, 7); // enable device info & T-UART services
    DELAY_milliseconds(200);
    RN487X_RebootCmd();         // reboot the device for the changes made
    DELAY_milliseconds(RN487X_STARTUP_DELAY);
    led_blink(2);               // ready signal
}

void read_data(volatile uint8_t* buffer) {
    int idx = 0;
    while (RN487X_DataReady()) {
        buffer[idx++] = RN487X_Read();
    }
}

void extrude(int length) {
    cw_turn(STEPPER_PORT, steps_from_length(length), STEPPER_DELAY);
}

void retract(int length) {
    cc_turn(STEPPER_PORT, steps_from_length(length), STEPPER_DELAY);
}

void strip() {
    rotate_pulse(STRIP_OFFSET_ANGLE, SERVO_PORT, SERVO_BIT);
}

void cut() {
    rotate_pulse(CUT_OFFSET_ANGLE, SERVO_PORT, SERVO_BIT);
}