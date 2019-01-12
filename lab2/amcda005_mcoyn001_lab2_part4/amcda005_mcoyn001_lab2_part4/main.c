/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 2 Exercise # 4
 *    Exercise Description: [optional - include for your own benefit]
 *      Disneyland.
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
///*
#include <avr/io.h>

int main(void)
{ 
	DDRA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0x00; 
	DDRC = 0x00; // Configure port D's 8 pins as outputs
	DDRD = 0xFF;
	
	PORTA = 0x00; // Initialize PORTA output to 0s
	PORTB = 0x00; // Initialize PORTB output to 0s
	PORTC = 0x00; // Initialize PORTC output to 0s
	PORTD = 0x00; // Initialize PORTD output to 0s
	unsigned char mask0 = 0x01; // mask to change 
	unsigned char mask1 = 0x02; // mask to change 
	unsigned char mask2 = 0xFC; // mask to change 

	unsigned char tmpA, tmpB, tmpC, tmpD, totalw, diffAC;
	while(1){
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PORTC; // There seems to be a bug in the simulator which prevents assigning to PINC in bits 2-5. 
		tmpD = PORTD;
		
		totalw = ( tmpA + tmpB + tmpC );
		
		if (tmpA >= tmpC) { diffAC = (tmpA - tmpC); }
		else { diffAC = (tmpC - tmpA); }
		
		if (totalw > 140) {
				tmpD = (tmpD & ~mask0) | (0x01 & mask0);
		}else tmpD = (tmpD & ~mask0) | (0x00 & mask0);
		
		if(diffAC > 80) {
			tmpD = (tmpD & ~mask1) | (0x02 & mask1);
		}else tmpD = (tmpD & ~mask1) | (0x00 & mask1);

		
		//shiftedw = totalw << 2;
		PORTD = (tmpD & ~mask2) | (totalw & mask2);
	}
	return 0;
}

