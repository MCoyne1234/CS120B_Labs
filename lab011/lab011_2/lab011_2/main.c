/*
 * lab011_2.c
 *
 * Created: 2/21/2019 4:23:27 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <io_alt.c>
#include <timer.h>

unsigned char stuff[] = "CS120B is Legend... wait for it DARY!";


enum State {SCROLL} state;
void Tick(){
        static unsigned char scroll = 16;
        static unsigned char disp = 0;
        static unsigned long offset_trigger = 0; 
        static unsigned long offset = 0;
        static unsigned long character_pos = 0 ;
        
        unsigned long mess_length = sizeof(stuff)/sizeof(stuff[0]) ;
    switch(state){
        case SCROLL:
                offset = 0;
                offset_trigger = 0;
                scroll = 15;
                LCD_ClearScreen();
                LCD_Cursor(16);
                
                for(int i = 0; i < (mess_length + 15); ++i){
                    //LCD_ClearScreen();
                    for(int j = 16; j > scroll; --j){
                        if( (character_pos = (j-scroll-1 + offset) ) >= (mess_length - 1) ) disp = 32;
                        else disp = stuff[character_pos];
                        
                        LCD_Cursor(j);
                        LCD_WriteData(disp);
                        
                    }
                    while(!TimerFlag);
                    TimerFlag = 0;
                    
                    if(scroll) --scroll;
                    ++offset_trigger;
                    if(offset_trigger >= 16) {
                        ++offset;
                    }                   
                }
        default: 
            state = SCROLL;
        break;
    }
    
}

int main(void)
{
    DDRA = 0xFF; PORTC = 0x00;
    DDRB = 0xFF; PORTC = 0x00;
    DDRC = 0xF0; PORTC = 0x0F; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
      
    TimerSet(400);
    TimerOn();
    TimerFlag = 0;
      
    //unsigned char stuff[] = "Matthew is Legend... wait for it DARY!";

    // Initializes the LCD display
    LCD_init();
    LCD_ClearScreen();
    while (1) 
    {  
        Tick();
        while(!TimerFlag);
        TimerFlag = 0;                
    }
}