/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 8 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      Change LED lights when a button is pressed. 
 *      Consider more transitions to capture long presses? The simple solution has poor behavior. 
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */


//Exercise 1: ADC using Potentiometer

#include <avr/io.h>
#include "io.c"
#include "timer.h"

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
    DDRB = 0xFF;
    DDRD = 0xFF;   
	ADC_init();
    TimerSet(100);
    TimerOn();
	unsigned short my_short= 0xABCD;
    unsigned char tmpB, tmpD;
	TimerFlag = 0;
    /* Replace with your application code */
    while (1) 
    {
		my_short = ADC; 
		tmpB = (0x00FF & my_short);	//(0000000011111111 & 0xABCD)
		tmpD = (my_short >> 8);			//shift over ADC 8 bits
	    PORTB = tmpB;
        PORTD = tmpD;
        while(!TimerFlag);
        TimerFlag = 0;	
	}
}

