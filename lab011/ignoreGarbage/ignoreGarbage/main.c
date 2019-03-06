/*
 * lab011_1.c
 *
 * Created: 2/19/2019 12:41:21 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <bit.h>
#include <timer.h>
#include <stdio.h>
#include <scheduler.h>
#include <io_alt.c>


void LCD_Custom_Char (unsigned char loc, unsigned char *msg){
    int i;
    LCD_WriteCommand (0x40 + (loc*8));	/* Command 0x40 for CGRAM */
    for(i = 0;i < 8; i++)	/* 8 cause 8 lines x 5 rows per character */
    LCD_WriteData(msg[i]);
    LCD_WriteCommand(0x80);
}

void KeypadTick(){

}


int main(void)
{
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F; // PORTB set to output, outputs init 0s
    DDRD = 0xFF; PORTD = 0x00; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
    //unsigned long keypad_time = 10;
    
    TimerSet(2000);
    TimerOn();
    TimerFlag = 0;
    
    LCD_init();
    //LCD_DisplayString(1,"HIDY-HO");

    // TOP right to bottom left. Only 5 bits per entry used => 5x8 pixels. 
	unsigned char sel3[8] = {0x1C, 0x1F, 0x1F, 0x1C, 0x00, 0x00, 0x00, 0x00};
	unsigned char sel0[8] = {0x00, 0x00, 0x00, 0x00, 0x1C, 0x1F, 0x1F, 0x1C};
	unsigned char selS[8] = {0x00, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char selE[8] = {0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char selC[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x00};
    unsigned char selX[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00};
	
	LCD_Custom_Char(0, sel3);		// build at position 0...
	LCD_Custom_Char(1, sel0);
	LCD_Custom_Char(2, selS);
	LCD_Custom_Char(3, selE);
	LCD_Custom_Char(4, selC);
    LCD_Custom_Char(5, selX);
    
    LCD_Cursor(1);
    LCD_WriteData(0);
    LCD_Cursor(3);
    LCD_WriteData(1);
    LCD_Cursor(5);
    LCD_WriteData(2);
    LCD_Cursor(7);
    LCD_WriteData(3);
    LCD_Cursor(9);
    LCD_WriteData(4);
    LCD_Cursor(11);
    LCD_WriteData(5);
    LCD_Cursor(13);
    LCD_WriteData(9);
        
    while(1) {
        while(!TimerFlag);
        TimerFlag = 0;
    }
        return 0;
}

