/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 2 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      The program will assign PORTB0 to 1 when PORTA == 1 AND PORTA1 == 0.
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
///*
#include <avr/io.h>

int main(void)
{ 
	DDRA = 0x00; // Configure port B's 8 pins as outputs
	DDRB = 0xFF; 
	//PORTA = 0x00; // Initialize PORTA output to 0s
	//PORTB = 0x00; // Initialize PORTB output to 0s

	while(1){
		//check if garage door is open and no light detected.
		if( (PINA & 0x01) == 0x01 && (PINA & 0x02) == 0x00) {
			PORTB = 0x01;
		}else { 
			PORTB = 0x00;
		}
	}
	return 0;
}
//*/
/*
#include <avr/io.h>

int main(void)
{
	DDRA = 0x00;
    DDRB = 0xFF; // Configure port B's 8 pins as outputs
    PORTB = 0x00; // Initialize PORTB output to 0’s
    while(1)
    {
		if(PINA == 0x01) PORTB = 0x0F; // Writes port B's 8 pins with 00001111
		else PORTB = 0x06;
    }
}
*/