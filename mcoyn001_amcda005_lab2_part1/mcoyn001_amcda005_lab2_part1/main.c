/*
 * mcoyn001_amcda005_lab2_part1.c
 *
 * Created: 1/9/2019 9:22:57 PM
 * Author : Administrator
 */ 

#include <avr/io.h>

int main(void)
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
	}
}


