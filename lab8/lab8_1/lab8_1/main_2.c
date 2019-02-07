/*
 * lab8parta.c
 *
 * Created: 2/6/2019 5:26:10 PM
 * Author : ashle
 */ 

//Exercise 1: ADC using Potentiometer

#include <avr/io.h>
#include "io.c"

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
	ADC_init();
	unsigned short my_short= 0xABCD;
	
    /* Replace with your application code */
    while (1) 
    {
		my_short = ADC; 
		PORTB = (0x00FF & my_short);	//(0000000011111111 & 0xABCD)
		PORTD = (my_short >> 8);			//shift over ADC 8 bits
		
	}
}

