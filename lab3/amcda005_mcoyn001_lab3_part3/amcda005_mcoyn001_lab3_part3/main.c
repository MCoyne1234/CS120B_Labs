/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 3 Exercise # 3
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    	DDRA = 0xFF;
		DDRB = 0xFF;
		DDRC = 0xFF;
		
		unsigned char tmpA, tmpC; 
	
	while (1) 
    {
		tmpA = PORTA;
		tmpC = PORTC;
		
		if((tmpA & (16 + 32 + 64)) == (16 + 32 + 64) ){
			PORTC = PORTC & 0x7F;
		}
		else if((tmpA & (16 + 32 )) == (16 + 32) ){
			PORTC = PORTC | 0x80;
		}
		
		
		if ((tmpA & 0x0F) == 0){
			PORTC = (PORTC & 0xC0) &(PORTC | 0x40) ;
		}
		else if ((tmpA & 0x0F) <= 2){
			PORTC = PORTC |(32 + 64 );
		}
		else if((tmpA & 0x0F) <=4){
			PORTC = (PORTC & 0) |(32 + 16 + 64);
		}
		else if((tmpA & 0x0F) <= 6){
			PORTC = PORTC |(32 + 16 + 8);
		}
		else if((tmpA & 0x0F) <= 9){
			PORTC = PORTC |(32 + 16 + 8 + 4);
		}
		else if((tmpA & 0x0F) <= 12){
			PORTC = PORTC |(32 + 16 + 8 + 4 + 2);
		}
		else if((tmpA & 0x0F) <= 15){
			PORTC = PORTC |(32 + 16 + 8 + 4 + 2 + 1);
		}
		
		
		if( (tmpA & 0x0F) > 2){
			PORTC = PORTC & 0xBF; 
		}
		
		PORTC = tmpC
    }
}

