/*
 * lab8part3.c
 *
 * Created: 2/6/2019 5:50:07 PM
 * Author : ashle
 */ 
//Exercise 3: Turning on/off an LED using a Photoresistor

#include <avr/io.h>

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
	unsigned short max = 0xFFFF; 
	
	/* Replace with your application code */
	while (1)
	{
		if(ADC >= (max/2)) {
			//illuminate LED
			PORTB = 0x01;
		}
		else if (ADC < (max/2)){
			//turn LED off
			PORTB = 0x00;
		}
		else {
			//error
		}
	}
}

