/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef RN4870_H_INCLUDED
#define	RN4870_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

void init_BLE(const char* name) ;
void send_message(const char* message);
void send_buffer(uint8_t *buffer, uint8_t len);
void capture_received_message(void);
void blocking_wait(uint16_t);
void ready_receive_buffer(void);
char* get_response(void);
char* send_and_wait(const char* sendString);

#endif	// RN4870_H_INCLUDED

