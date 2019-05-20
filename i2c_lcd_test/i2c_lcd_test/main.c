/*

 * lcd_i2cmaster_test.c

 *

 * Created: 03/06/2014 11:07:15

 *  Author: David Prentice

 */ 

#include <avr/io.h>

#include <util/delay.h>

#include "lcd.h"
#include "lcd.c"


//extern void lcd_backlight(char on);    //not in lcd.h


int main(void)

{
    
    DDRC = 0xFF;

    lcd_init(LCD_ON_DISPLAY);

	//lcd_backlight(0);

	_delay_ms(500);

	//lcd_backlight(1);

	_delay_ms(500);

	while(1)

    {

        lcd_clrscr();

		lcd_gotoxy(0, 0);

		lcd_puts_P("Hello World");

		lcd_gotoxy(1, 1);

		lcd_puts("Second Line");

		_delay_ms(1000);

    }

}



