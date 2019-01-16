/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 3 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      The program will assign PORTB0 to 1 when PORTA == 1 AND PORTA1 == 0.
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */


#include <avr/io.h>

int main(void)
{	
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0x00; PORTC = 0x00;
	
	unsigned short tmpA = 0x00;
	unsigned short tmpB = 0x00;
	unsigned short A_B = 0x0000;
	unsigned char count = 0;
	unsigned short mask = 0x0001;
	
    while(1)
    {
		 tmpA = PORTA;
		 tmpB = PORTB;
		 A_B = (0x00 | tmpA);
		 A_B = A_B << 8;
		 A_B = (A_B | tmpB);
		 count = 0;
		 mask = 0x0001;
		 
		 for(unsigned char i = 0; i < 16; ++i){
			 
			 if( (A_B & mask) == mask ){
				++count;
			 }
			 mask = mask << 1;
		 }
		
		PORTC = count;
    }
	
	return 0;
}

