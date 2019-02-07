/*
 * testLCD.c
 *
 * Created: 2/3/2019 4:29:10 PM
 * Author : ashle
 */ 

#include <avr/io.h>
#include "io.c"

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	
	// Initializes the LCD display
	LCD_init();
	
	// Starting at position 1 on the LCD screen, writes Hello World
	LCD_DisplayString(1, "Hello World");
	
	while(1) {continue;}
}
