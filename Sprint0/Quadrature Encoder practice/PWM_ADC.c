// ------- Preamble -------- //
#include <avr/io.h>              /* Defines pins, ports, etc */
#include <util/delay.h>          /* Functions to waste time */

  // -------- Functions -------- //
  static inline void initPWM(void) {
    TCCR1A |= (1 << WGM10);   // set fast PWM mode, pt. 1
    TCCR1B |= (1 << WGM12);   // set fast PWM mode, pt. 2
    TCCR1B |= (1 << CS11);    // set scaler for frequency: cpu clock / 8
	TCCR0A |= (1 << WGM00);   // set fast PWM mode, pt. 1
	TCCR0B |= (1 << WGM01);   // set fast PWM mode, pt. 2
	TCCR0B |= (1 << CS11);    // set scaler for frequency: cpu clock / 8
	TCCR0A |= (1 << COM1A1);  // enable PWM on OCR0A (PD6); non-inverting mode
    TCCR1A |= (1 << COM1A1);  // enable PWM on OCR1A (PB1); non-inverting mode
	TCCR1A |= (1 << COM1B1);  // enable PWM on OCR1B (PB2); non-inverting mode
    DDRB   |= (1 << PB1) | (1 << PB2);     // set PB1 as outout
	DDRD |= (1 << PD6);
  }

int main(void) {

  // -------- Inits --------- //
  initPWM();
  PINC |= 1;  //invert pin input, return 0 when -5v sensed and 1 when 0v sensed
  OCR1A = 0;
  OCR1B = 0;
  OCR0A = 0;

  uint16_t adcValue;
  int light = 0;
  int oldA = 1; //set the oldA as HIGH
  int oldB = 1; //set the oldB as HIGH

  // ------ Event loop ------ //
  while (1) {
	  if ((PINC & 1) == 0) {
		  while ((PINC & 1) == 0) {
		  }
		  light = (light + 1) % 3;
	  }
	  int result = 0;
	  int newA = (PINC & (1 << 3)) >> 3;//read the value of clkPin to newA
	  int newB = (PINC & (1 << 4)) >> 4;//read the value of dtPin to newB
	if (newA != oldA || newB != oldB) //if the value of clkPin or the dtPin has changed
	{
		//If rotation direction is determined output info
		if (oldA == 1 && newA == 0)
		{
			result = (oldB * 2 - 1);
		}
	}
	oldA = newA;
	oldB = newB;
	if (light == 0) {
		OCR1A += result * 3;   // set the PWM duty cycle (truncates 8 MSB, since OCR1A 8-bit register)
	}
	else if (light == 1) {
		OCR0A += result * 3;   // set the PWM duty cycle (truncates 8 MSB, since OCR0A 8-bit register)
	}
	else if (light == 2) {
		OCR1B += result * 3;   // set the PWM duty cycle (truncates 8 MSB, since OCR1B 8-bit register)
	}
    
  }                              /* End event loop */
  return 0;                      /* This line is never reached */
}
