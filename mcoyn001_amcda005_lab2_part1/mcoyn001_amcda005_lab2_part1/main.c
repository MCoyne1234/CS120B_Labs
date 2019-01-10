/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 2 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      The program will assign A input value to B and so on.
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{ 
	DDRA = 0x00; // Configure port B's 8 pins as outputs
	DDRB = 0xFF; 
	PORTB = 0x00; // Initialize PORTB output to 0’s
	//PORTA = 0x00;
	// 0000 0001	 = 0x01
	while(1){
	//check if garage door is open
		if( PORTA0 == 0x01 && PORTA1 == 0x00) {
			PORTB= 0x01;
		}
	}
}


