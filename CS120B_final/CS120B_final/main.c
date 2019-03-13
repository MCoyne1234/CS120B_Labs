/*
 * CS120B_final.c
 *
 * Created: 3/11/2019 5:17:57 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>

#include "SNES.c"
#include "io.c"
#include "scheduler.h"
#include "timer.h"

enum StatesSNES {SNES_LISTEN};
enum StatesGame{GAME_BEGIN, GAME_PLAY, GAME_OVER};
    
// States shared between tasks.    
unsigned short SNES_button;
unsigned char tank_pos, fire_b;

// Forward declarations. 
int SNESInput(int state); 
int Game(int state);    
void CreatePremadeChars();

int main(void)
{
    DDRA = 0x03; PORTA = 0x00; // input for SNES controller
    DDRB = 0xFF; PORTB = 0x00; // LCD output
    DDRC = 0xFF; PORTC = 0x00; // LCD output
    DDRD = 0xFF; PORTD = 0x00; // LCD output
    
    static task task_SNES, task_game;
    task *tasks[] =  {&task_SNES, &task_game};    
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    
    unsigned long period_SNES = 80;
    unsigned long period_game = 80; 
    
    task_SNES.state = -1;
    task_SNES.period = period_SNES; //should get input every system tick.
    task_SNES.elapsedTime = period_SNES;
    task_SNES.TickFct = &SNESInput;
    
    task_game.state = -1;
    task_game.period = period_game;
    task_game.elapsedTime = period_game;
    task_game.TickFct = &Game;
    

    TimerSet(1);
    TimerOn();
    
    TimerFlag = 0;
    
    LCD_init(); 
    
    CreatePremadeChars();
    LCD_ClearScreen();    
    //LCD_Cursor(1);
    //LCD_WriteData(0);
    //LCD_WriteData(1);
    //LCD_WriteData(2);
    //LCD_WriteData(3);
    //LCD_DisplayString(1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ!");
    //
    SNES_init();
    unsigned short i = 0; // Scheduler for-loop iterator
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


int SNESInput(int state){
    switch(state){
        case SNES_LISTEN:
            SNES_button = SNES_Read();
            ///*
                    //if((button & 1) == 1) output |= 0x0A;
                    //if((button & 2) == 2) output |= 0xA0;
                    //if((button & 4) == 4) output |= 0xAA;
                    //if((button & 8) == 8) output |= 0xFF;
           ///*
            if(SNES_button){
                if((SNES_button & 16) == 16); //output += "R";
                if((SNES_button & 32) == 32);//output += "L";
                if((SNES_button & 64) == 64); //output += "X";
                if((SNES_button & 128) == 128); //output += "A";
                if((SNES_button & 256) == 256){  //output += "Right";
                    if(tank_pos > 0 ) --tank_pos;
                } 
                if((SNES_button & 512) == 512){  //output += "Left";
                    if(tank_pos < 3) ++tank_pos;
                } 
                if((SNES_button & 1024) == 1024); //output += "Up";
                if((SNES_button & 2048) == 2048); //output += "Down";
                if((SNES_button & 4096) == 4096); //output += "Start";
                if((SNES_button & 8192) == 8192); //output += "Select";
                if((SNES_button & 16384) == 16384); //output += "Y";
                if((SNES_button & 32768) == 32768); //output += "B";
            }else SNES_button = 0;
          //  */
        break;
        default:
            state = SNES_LISTEN;
        break;
    }
    return state;
};

int Game(int state){
    switch(state){
        static unsigned char begin = 0x00; 
        case GAME_BEGIN: 
            tank_pos = 0;
            if(!begin){
                //LCD_Cursor(3);
                //LCD_ClearScreen();
                //LCD_Cursor(0);
                LCD_DisplayString(1,"Press Start...");
                begin = ~begin;
            }
            if((SNES_button & 4096) == 4096){
            //if((SNES_button)){
                state = GAME_PLAY;
                LCD_ClearScreen();
            }

            // convert 123 to string [buf]
           // itoa(num, snum, 10);
           // LCD_DisplayString(1,snum);
          //  _delay_ms(30000);
        break;
        case GAME_PLAY:
        
            if(tank_pos == 0){
                LCD_Cursor(1);
                LCD_WriteData(0);
            }else if(tank_pos == 1){
                LCD_Cursor(17);
                LCD_WriteData(32);
                LCD_Cursor(1);
                LCD_WriteData(1);
            }else if(tank_pos == 2){
                LCD_Cursor(1);
                LCD_WriteData(32);
                LCD_Cursor(17);
                LCD_WriteData(0);
            }else if(tank_pos == 3){
                LCD_Cursor(17);
                LCD_WriteData(1);
            }    
        
        break;  
        case GAME_OVER:
        
        break;
        default: 
            state = GAME_BEGIN;
        break;      
    }
    return state;
}

void LCD_Custom_Char (unsigned char loc, unsigned char *msg){
    int i;
    LCD_WriteCommand (0x40 + (loc*8));	/* Command 0x40 for CGRAM */
    for(i = 0;i < 8; i++)	/* 8 cause 8 lines x 5 rows per character */
    LCD_WriteData(msg[i]);
    LCD_WriteCommand(0x80);
}

void CreatePremadeChars(){
    unsigned char tank_T[8] = {0x1C, 0x1F, 0x1F, 0x1C, 0x00, 0x00, 0x00, 0x00};
    unsigned char tank_B[8] = {0x00, 0x00, 0x00, 0x00, 0x1C, 0x1F, 0x1F, 0x1C};
    unsigned char thing_TB[8] = {0x00, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char thing_TF[8] = {0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char selC[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x00};
    unsigned char selX[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00};
        
    LCD_Custom_Char(0, tank_T);
    LCD_Custom_Char(1, tank_B);
    LCD_Custom_Char(2, thing_TB);
    LCD_Custom_Char(3, thing_TF);
}