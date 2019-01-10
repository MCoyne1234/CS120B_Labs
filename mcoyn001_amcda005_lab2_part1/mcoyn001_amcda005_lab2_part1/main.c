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
	DDRB = 0xFF; // Configure port B's 8 pins as outputs
	PORTB = 0x00; // Initialize PORTB output to 0�s
	while(1)
	{
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
}


