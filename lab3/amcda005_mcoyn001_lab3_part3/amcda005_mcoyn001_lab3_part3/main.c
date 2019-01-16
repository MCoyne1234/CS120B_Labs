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
			tmpC = tmpC & 0x7F;
		}
		else if((tmpA & (16 + 32 )) == (16 + 32) ){
			tmpC = tmpC | 0x80;
		}
		
		
		if ((tmpA & 0x0F) == 0){
			tmpC = (tmpC & 0xC0) &(tmpC | 0x40) ;
		}
		else if ((tmpA & 0x0F) <= 2){
			tmpC = tmpC |(32 + 64 );
		}
		else if((tmpA & 0x0F) <=4){
			tmpC = tmpC |(32 + 16 + 64);
		}
		else if((tmpA & 0x0F) <= 6){
			tmpC = tmpC |(32 + 16 + 8);
		}
		else if((tmpA & 0x0F) <= 9){
			tmpC = tmpC |(32 + 16 + 8 + 4);
		}
		else if((tmpA & 0x0F) <= 12){
			tmpC = tmpC |(32 + 16 + 8 + 4 + 2);
		}
		else if((tmpA & 0x0F) <= 15){
			tmpC = tmpC |(32 + 16 + 8 + 4 + 2 + 1);
		}
		
		
		if( (tmpA & 0x0F) > 2){
			tmpC = tmpC & 0xBF; 
		}
		
		PORTC = tmpC;
    }
}

