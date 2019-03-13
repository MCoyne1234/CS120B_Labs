/*
 * EEPROM_test.c
 *
 * Created: 3/11/2019 3:20:18 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include <io.h>
#include <io.c>

int main(void)
{
    DDRC = 0xFF;
    DDRD = 0xFF;
    
    unsigned char stuff[] = "This is a sentence to test EEPROM.";
    unsigned char size = sizeof(stuff)/sizeof(unsigned char);
    
    eeprom_write_block((void*)&stuff, (void*)16, size);
    
    LCD_init();
    LCD_ClearScreen();
    //LCD_Cursor(1);
    
    /* Replace with your application code */
    unsigned char stuff_read[size];
    eeprom_read_block((void*)&stuff_read, (const void*)16, size);
    //LCD_DisplayString(6,"DISPLAY");

    LCD_DisplayString(1,stuff_read);
    while (1) 
    {
    }
}

