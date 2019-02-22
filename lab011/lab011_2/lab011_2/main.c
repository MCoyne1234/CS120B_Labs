/*
 * lab011_2.c
 *
 * Created: 2/21/2019 4:23:27 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <io_alt.c>
#include <timer.h>

int main(void)
{
    DDRA = 0xFF; PORTC = 0x00;
    DDRB = 0xFF; PORTC = 0x00;
    DDRC = 0xF0; PORTC = 0x0F; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
      
    TimerSet(500);
    TimerOn();
    TimerFlag = 0;
      
    unsigned char stuff[] = "CS120B is Legend... wait for it DARY!";
    // Initializes the LCD display
    LCD_init();
    LCD_ClearScreen();
    //LCD_DisplayString(16, "");  
   
    unsigned char scroll = 16; 
    unsigned char disp;
    unsigned long character_pos = 0 ;
    
    unsigned long mess_length = sizeof(stuff)/sizeof(stuff[0]);
    while (1) 
    {
        scroll = 16;
        LCD_ClearScreen();
        LCD_Cursor(16);
        
        for(int i = 0; i < (mess_length ); ++i){         
            for(int j = 16; j >= scroll; --j){
                if( (character_pos = i + (j-scroll) ) >= (mess_length - 1) ) disp = 32;
                else disp = stuff[character_pos];
                                
                LCD_Cursor(j);
                LCD_WriteData(disp);                      
            }          
            if(scroll >= 1) --scroll;
            while(!TimerFlag);          
            TimerFlag = 0;
            
        }          
        
        
    }
}