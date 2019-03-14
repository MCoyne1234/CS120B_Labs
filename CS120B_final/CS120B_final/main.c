/*
 * CS120B_final.c
 *
 * Created: 3/11/2019 5:17:57 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include <string.h>

#include "SNES.c"
#include "io.c"
#include "scheduler.h"
#include "timer.h"

#define HIGH_SCORE_ADDR 0

enum StatesSNES {SNES_LISTEN};
enum StatesGame{GAME_BEGIN, GAME_PLAY, GAME_OVER};
    
// Vars shared between tasks.    
unsigned short SNES_button;
unsigned char tank_pos, fire_b;

unsigned char projectile[2];
unsigned char proj_pos;
unsigned char proj_flip;

unsigned char giant[2];
unsigned char giant_on;
unsigned char game_over_flag;
unsigned char score;

unsigned char limiter, counter;

// Forward declarations. 
int SNESInput(int state); 
int Game(int state);    
void CreatePremadeChars();
void ProcessInput();
void MoveTank();
void FireProjectile();
void MoveGiant();

int main(void)
{
    eeprom_write_byte((uint8_t)0, 0);
    
    DDRA = 0x03; PORTA = 0x00; // input for SNES controller
    DDRB = 0xFF; PORTB = 0x00; // LCD output
    DDRC = 0xFF; PORTC = 0x00; // LCD output
    DDRD = 0xFF; PORTD = 0x00; // LCD output
    
    static task task_SNES, task_game;
    task *tasks[] =  {&task_SNES, &task_game};    
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    
    unsigned long period_SNES = 100;
    unsigned long period_game = 100; 
    
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
        //fire_b = 0x00;
        case SNES_LISTEN:
            SNES_button = SNES_Read();
            ProcessInput();
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
            score = 0;
            tank_pos = 0;
            proj_pos = 0;
            proj_flip = 0;
            fire_b = 0;
            game_over_flag = 0;
            giant_on = 0;
            limiter = 10;
            counter = 0;
            
            if(!begin){
                char message[32];
                unsigned char high_score= eeprom_read_byte(0);
                char high_score_string[4];
                itoa((int)high_score,*high_score_string, 10);
                
                strcpy(message, "Press Start...  HIGH SCORE: ");
                strcat(message, high_score_string);
                LCD_DisplayString(1,message); // write to LCD only once on entry.
                begin = ~begin;
            }
            if((SNES_button & 4096) == 4096){
                state = GAME_PLAY;
                LCD_ClearScreen();
            }
        break;
        case GAME_PLAY:
        MoveTank();    
        if(fire_b & 0x0F){ FireProjectile();}
        MoveGiant();
        
        if(game_over_flag){ state = GAME_OVER;}
        
        break;  
        case GAME_OVER:
            if(begin){
                LCD_ClearScreen();
                LCD_DisplayString(4, "GAME OVER");
                begin = 0x00;
            }                
            if((SNES_button & 4096) == 4096){
                state = GAME_BEGIN;
            }
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
    unsigned char shot_TB[8] = {0x00, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char shot_TF[8] = {0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char shot_BB[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x00};
    unsigned char shot_BF[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00};
    unsigned char giant_T[8] = {0x1A, 0x0F, 0x0F, 0x1A, 0x00, 0x00, 0x00, 0x00};
    unsigned char giant_B[8] = {0x00, 0x00, 0x00, 0x00, 0x1A, 0x0F, 0x0F, 0x1A};
        
    LCD_Custom_Char(0, tank_T);
    LCD_Custom_Char(1, tank_B);
    LCD_Custom_Char(2, shot_TB);
    LCD_Custom_Char(3, shot_TF);
    LCD_Custom_Char(4, shot_BB);
    LCD_Custom_Char(5, shot_BF);
    LCD_Custom_Char(6, giant_T);
    LCD_Custom_Char(7, giant_B);
}

void ProcessInput(){
    // set all the shared vars according to SNES buttons pressed
    if(SNES_button){
        if((SNES_button & 16) == 16); //output += "R";
        if((SNES_button & 32) == 32);//output += "L";
        if((SNES_button & 64) == 64); //output += "X";
        if((SNES_button & 128) == 128); //output += "A";
        if((SNES_button & 256) == 256){  //output += "Right"; 
        } 
        if((SNES_button & 512) == 512){  //output += "Left";                  
        } 
        if((SNES_button & 1024) == 1024){ //output += "Up";
            if(tank_pos < 3) ++tank_pos;
        }                    
        if((SNES_button & 2048) == 2048){ //output += "Down";
            if(tank_pos > 0 ) --tank_pos;     
        }                
        if((SNES_button & 4096) == 4096); //output += "Start";
        if((SNES_button & 8192) == 8192); //output += "Select";
        if((SNES_button & 16384) == 16384); //output += "Y";
        if((SNES_button & 32768) == 32768){ //output += "B";
            //only fire one projectile at a time. FireProjectile() resets the flag.  
            if ( !(fire_b & 0x0F) ){ 
                projectile[0] = tank_pos; 
                if(tank_pos == 0){
                    projectile[1] = 1; 
                }else if(tank_pos == 1){
                    projectile[1] = 1;
                }else if(tank_pos == 2){
                    projectile[1] = 17;
                }else if(tank_pos == 3){
                    projectile[1] = 17;
                }
            }                    
            fire_b = 0x0F;                    
        }                    
    }else {SNES_button = 0;
    PORTC = 0x00;}
   
   return; 
}

void MoveTank(){
    
    //Move the tank by half a character each time.
    if(tank_pos == 0){
        LCD_Cursor(1);
        LCD_WriteData(32);
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
        LCD_WriteData(32);      
        LCD_Cursor(17);
        LCD_WriteData(1);
    }
    return;
}

void FireProjectile(){
    
    // making a note to get rid of this 
    if(projectile[0] == 0){
        LCD_Cursor(projectile[1]);
    }else if(projectile[0] == 1){
        LCD_Cursor(projectile[1]);
    }else if(projectile[0] == 2){
        LCD_Cursor(projectile[1]);
    }else if(projectile[0] == 3){
        LCD_Cursor(projectile[1]);
    }
    
 
    if(proj_pos > 15){
        LCD_Cursor(16);
        LCD_WriteData(32);
        LCD_Cursor(32);
        LCD_WriteData(32);        
        proj_pos = 0;
        fire_b = 0;
    }else {        
        LCD_Cursor(projectile[1] - 1);
        LCD_WriteData(32); 
        ++(projectile[1]);
        ++proj_pos;
        }
        
        if (proj_pos > 1)
        {
        
        if( (projectile[0] == 0) || (projectile[0] == 2) ){
            if(proj_flip){
                LCD_WriteData(2);
                }else{
                LCD_WriteData(3);
            }
        }else
            if(proj_flip){
                LCD_WriteData(4);
            }else{
                LCD_WriteData(5);
        }
        }        
        proj_flip = ~proj_flip;    
}

void MoveGiant(){
    unsigned short rand_n = rand();
       
    if(!giant_on){
        giant_on = 0xFF;
        if(rand_n <= 0x00FF){
            giant[0] = 0;
            giant[1] = 16;
        }else{ 
            giant[0] = 2;
            giant[1] = 32;
        }        
    }else{
     if(counter > limiter){   
        LCD_Cursor(giant[1]);
        LCD_WriteData(32);
                
        if(rand_n <= 0x000F){
            if(giant[0] < 3){++(giant[0]);}
        }else if(rand_n <= 0x00FF){
            if(giant[0] > 0){--(giant[0]);}
        }else {
            --(giant[1]);
        }
     counter = 0;  
     }else ++counter; 
    }
    
    LCD_Cursor(giant[1]);
    if((giant[0] == 0) || (giant[0] == 2)){
        LCD_WriteData(6);
    }else if((giant[0] == 1) || (giant[0] == 3)){
        LCD_WriteData(7);
    }
    
    if((giant[1] == 1) || (giant[1] == 16)) {game_over_flag = 0xFF;}
    
    if( (projectile[0] == giant[0]) && (projectile[1] == giant[1]) ){
        ++score;
        if(limiter > 0 ) --limiter;
        LCD_Cursor(giant[1]);
        LCD_WriteData('#');
        //LCD_WriteData(32);
        giant_on = 0x00;
    }  
    
}