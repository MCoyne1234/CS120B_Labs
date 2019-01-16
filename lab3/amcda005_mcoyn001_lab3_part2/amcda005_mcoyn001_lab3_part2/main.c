/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 3 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    	DDRA = 0x00;
		DDRB = 0xFF;
		DDRC = 0xFF;
		
		unsigned char tmpA; 
	
	while (1) 
    {
		tmpA = PORTA;
		if (tmpA <= 2){
			PORTC = (32 + 64 );
		}
		else if(tmpA <=4){
			PORTC = (32 + 16 + 64);
		}
		else if(tmpA <= 6){
			PORTC = (32 + 16 + 8);
		}
		else if(tmpA <= 9){
			PORTC = (32 + 16 + 8 + 4);
		}
		else if(tmpA <= 12){
			PORTC = (32 + 16 + 8 + 4 + 2);
		}
		else if(tmpA <= 15){
			PORTC = (32 + 16 + 8 + 4 + 2 + 1);
		}

    }
}

