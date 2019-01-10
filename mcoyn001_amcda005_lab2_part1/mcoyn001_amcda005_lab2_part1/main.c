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
<<<<<<< HEAD
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
=======
{
	//1 means car is parked in space
	//4 spaces
	unsigned char cntavail;	//spaces available counter
	
	DDRA = 0xF0;    // Configure port A's pins as outputs
	PORTB = 0x00;   // Initialize PORTB output to 0’s
	DDRC == 0xFF; 
	PORTC = 0x00;   //init
	cntavail = 4;   //start off with 4 empty spaces, 
	//want to output number of empty spaces
	unsigned char counter = 0x00;
	counter = PINA; 
	while(1)
	{
		counter = cntavail;
		if(PINA & 0x01 == 0x00){}
		else{
			counter -= 1; 
		}
		if(PINA & 0x02 == 0x00 ){}
		else{
    		counter -= 1;
		}
		if(PINA & 0x04 == 0x00 ){}
		else{
    		counter -= 1;
		}
		if(PINA & 0x08 == 0x00 ){}
		else{
			counter -= 1;
		}
		PORTC = counter; //write output
>>>>>>> matt_lab2
	}
}


