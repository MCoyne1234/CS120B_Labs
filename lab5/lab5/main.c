/*
 * lab5.c
 *
 * Created: 1/22/2019 12:58:27 PM
 * Author : ashle
 */ 


#include <avr/io.h>

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	while(1)
	{
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
}


