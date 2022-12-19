#include "Uart.h"
#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

void Pwm_Init(void) {
    
    /* Set fast PWM mode with non-inverted output*/
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1<<COM0A1) ;
    /* No prescaller */
    TCCR0B = (1<<CS00);
	DDRB |= (1 << PIN6);  /* set OC0A pin as output*/

}

/* 000 -> 0% Duty Cycle 
   255 -> 100% Duty Cycle
*/
void Pwm_SetDuty(unsigned char DutyCycle)
{
    OCR0A = DutyCycle;
}