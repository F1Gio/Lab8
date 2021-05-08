/*	Author: gturr001, Giovany Turrubiartes
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #8  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM(double frequency) {
	static double current_frequency;

	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } 
		else { TCCR3B |= 0x03; }

		if (frequency < 0.954) {
			OCR3A = 0xFFFF;
		}

		else if (frequency > 31250) {
			OCR3A = 0x0000;
		}

		else {
			OCR3A = (short)(8000000 / (128 * frequency)) - 1; 
		}

		TCNT3 = 0;
		current_frequency = frequency;

	}
}

void PWM_on () {
	TCCR3A = (1 << COM3A0);

	TCCR3B = (1 << WGM32);

	set_PWM(0);

}
void PWM_off () {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	unsigned char button1 = 0x00;
	unsigned char button2 = 0x00;
	unsigned char button3 = 0x00;
	DDRB = 0x40; 
	PORTB = 0x00;


	PWM_on();

    /* Insert DDR and PORT initializations */
	
    /* Insert your solution below */
    while (1) {

//	    PWM_on();

	    button1 = ~PINA & 0x01;
	    button2 = ~PINA & 0x02;
	    button3 = ~PINA & 0x04;

	    if ((button1 && button2) || (button2 && button3) || (button1 && button3)) {
		    set_PWM(0);
	    }

	    else if (button1) {
		set_PWM(261.63);
	    }


	    else if (button2) {
		    set_PWM(293.66);
	    }


	    else if (button3) {
		    set_PWM(329.63);

	    }


	    else {
		set_PWM(0);
	    }



    }
}
