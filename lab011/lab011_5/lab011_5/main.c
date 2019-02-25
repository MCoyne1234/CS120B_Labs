/*
 * lab011_5.c
 *
 * Created: 2/22/2019 1:32:40 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <keypad.h>
#include <io_alt.c>
#include <timer.h>
#include <scheduler.h>

unsigned char shared_pause = 0x00;
unsigned char shared_cursor = 5;

enum StatesKeypad {KEYPADLISTEN, KEYPADACTION};
//enum StatesButton {BUTTON_LISTEN, UP, DOWN};
enum StatesLCD {PAUSE, PLAY, GAMEOVER};    
  
int Keypad_in(int state){
    static unsigned char tempB, counter = 0;
    tempB = PINB & 0x07;  

    switch (state){
        case KEYPADLISTEN:
            if(tempB) ++counter;
            else counter = 0;
            
            if(counter >= 1){
               state = KEYPADACTION; 
            }
        break;
        case  KEYPADACTION:
            if(tempB == 0x01){
                shared_cursor = 5;
            }else if(tempB == 0x02){
                shared_cursor = 21;               
            }else if(tempB == 0x04){
                shared_pause = ~shared_pause;
            }
            state = KEYPADLISTEN;
        break;
        default:
            state = KEYPADLISTEN; 
        break;        
   }
    return state;
}
  
int LCD_out(int state){
    static unsigned char obs_top_pos = 16, obst_bottom_pos = 32;
    static unsigned char top_start = 16, bottom_start = 32, offset = 0;
    
    switch (state){
        case PAUSE:
            if(shared_pause){ 
                state = PLAY;
                LCD_ClearScreen();
            }
        break;
        case PLAY:
            if(!shared_pause) { 
                state = PAUSE; 
                break;
            };            
            
            if(obs_top_pos > 1){
                LCD_Cursor(obs_top_pos);
                LCD_WriteData(' ');
                --obs_top_pos;}
            else {
                LCD_Cursor(1);
                LCD_WriteData(' ');
                obs_top_pos = top_start;
            }
            LCD_Cursor(obs_top_pos);
            LCD_WriteData('{');                        
            
            if(offset > 7){
               if(obst_bottom_pos > 17){
                   LCD_Cursor(obst_bottom_pos);
                   LCD_WriteData(' ');
                    --obst_bottom_pos;}
               else {
                   LCD_Cursor(17);
                   LCD_WriteData(' ');
                   obst_bottom_pos = bottom_start;
               }
               LCD_Cursor(obst_bottom_pos);
               LCD_WriteData('<');
            }else{++offset;}            
            LCD_Cursor(shared_cursor);
            
            if( (shared_cursor == obs_top_pos) || (shared_cursor == obst_bottom_pos) ) state = GAMEOVER;
        break;
        case GAMEOVER:
            LCD_ClearScreen();
            LCD_DisplayString(4, "GAME OVER");
            shared_pause = 0x00;
            //offset = 0;
            //obs_top_pos = top_start; 
            //obst_bottom_pos = bottom_start;
            state = PAUSE;
        break;
        default:
        //state = PLAY;
        state = PAUSE;
        break;   
    }
    return state;
}

int main(void)
{
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0x00; PORTB = 0x00;
    DDRC = 0x00; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    static task task1, task2;
    task *tasks[] = { &task1, &task2};
    unsigned long KeypadTime = 4;
    unsigned long LCDTime = 50;
        
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    
    task1.state = -1;//Task initial state.
    task1.period = KeypadTime;//Task Period.
    task1.elapsedTime = KeypadTime; // Task current elasped time.
    task1.TickFct = &Keypad_in; // Function pointer for the tick.
    
    task2.state = -1;//Task initial state.
    task2.period = LCDTime;//Task Period.
    task2.elapsedTime = LCDTime; // Task current elasped time.
    task2.TickFct = &LCD_out; // Function pointer for the tick.
    // Set the timer and turn it on
    TimerSet(5);
    TimerOn();
    
    LCD_init();
    LCD_ClearScreen();

    unsigned short i; // Scheduler for-loop iterator
        while(1){
            // Scheduler code
            for ( i = 0; i < numTasks; i++ ) {
                // Task is ready to tick
                if ( tasks[i]->elapsedTime == tasks[i]->period ) {
                    // Setting next state for task
                    tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                    // Reset the elapsed time for next tick.
                    tasks[i]->elapsedTime = 0;
                }
                tasks[i]->elapsedTime += 1;
            }
            while(!TimerFlag);
            TimerFlag = 0;
        }
        // Error: Program should not exit!
        return 0;
    }