/*
 * testBuzzer.c
 *
 * Created: 2/13/2019 1:28:52 PM
 * Author : ashle
 */ 

#include <avr/io.h>
#include "timer.h"

int main(void)
{
    DDRA = 0x00; PORTA = 0X00;
	DDRB = 0xFF; PORTB = 0X00;// init
	 
	unsigned char temp_a = 0x00; 
	int count = 0; //buzzer count for 2 ms
	
	TimerSet(1); //set timer to 1 ms
	TimerOn();   //turn timer on
	TimerFlag = 0;    
	
    while (1) 
    {
		temp_a = (PINA & 0x04); 
		if(temp_a && (count < 2)){
			PORTB = (PORTB^0xFF); 
			count++; //increment count until 2 
		}
		else{
			count = 0; //reset counter
			PORTB = 0x00; 
		}
		while(!TimerFlag){}
		TimerFlag = 0; 
		temp_a = 0; 
    }
}

