/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 2 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      The program will assign A input value to B and so on.
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
	//1 means car is parked in space
	//4 spaces
	unsigned char cntavail;	//spaces available counter
	
	DDRA = 0xF0;    // Configure PORTA's pins as outputs
	PORTA = 0x00;   // Initialize PORTA to 0’s
	
	DDRC == 0xFF; 
	PORTC = 0xFF;   // init
	
	cntavail = 4;   //start off with 4 empty spaces, 
	//want to output number of empty spaces
	unsigned char counter = 0x00;
	
	while(1)
	{
		counter = cntavail;
		if( (PINA & 0x01) == 0x00){}
		else{
			counter -= 1; 
		}
		if( (PINA & 0x02) == 0x00 ){}
		else{
    		counter -= 1;
		}
		if( (PINA & 0x04) == 0x00 ){}
		else{
    		counter -= 1;
		}
		if( (PINA & 0x08) == 0x00 ){}
		else{
			counter -= 1;
		}
		PORTC = counter; //write output
	}
}