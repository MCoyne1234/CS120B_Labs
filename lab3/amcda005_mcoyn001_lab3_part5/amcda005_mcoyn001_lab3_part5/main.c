/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 3 Exercise # 5
 *    Exercise Description: [optional - include for your own benefit]
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
	DDRD = 0x00; PORTD = 0x00; // Init D to input;
	DDRB = 0xFE; PORTB = 0x00; // Init B with B[7-1] output, B0 input.

    unsigned short weight = 0x0000;
	unsigned char tempD, tempB; 
	while (1) 
    {
		tempD = PIND;
		tempB = PINB;
		weight = (tempD << 1) | (tempB & 0x01);
		if(weight >= 70) {
			tempB = (tempB | 0x02);
		}else if(weight > 5){
			tempB = (tempB & 0x01) | (0x04);
		}else{
			tempB = (tempB & 0x01);
		}
		PORTB = tempB;
    }
}

