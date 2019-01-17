/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 4 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      Change LED lights when a button is pressed. 
 *      Consider more transitions to capture long presses? The simple solution has poor behavior. 
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>

enum States {B0_ON, B1_ON} state;
unsigned char tmpA;

void Tick(){
	
	switch(state){
		case B0_ON : 
			PORTB = 0x01;
		break;
		case B1_ON :
			PORTB = 0x02;
		break;
		default :
		// error
		break;
	}
	
	tmpA = PINA; // read from A to see if button is pressed. 
	switch(state){
		case B0_ON : 
			if(tmpA & 0x01) state = B1_ON;
		break;
		case B1_ON :
			if(tmpA & 0x01) state = B0_ON;
		break;	
		default :
			// error
		break;
	}
	//tmpA = 0;
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		DDRA = 0x00; // INIT A to input;
		DDRB = 0xFF; // INIT B to output;
		
		PORTB = 0x01;
		
		while(1) Tick();
    }
}

