/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 7 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 
#include <avr/io.h>
#include "timer.h"
#include <io.c>


enum States{ RESTART, BD, PAUSE, ONE, TWO, THREE, WIN} state, prev, next, p_s;
unsigned char button, pressed, released, is_paused, score, win_b, tmpB;
unsigned long period = 300; // period before each transition is; 
const unsigned char win_mess[] = "You Win!";
const unsigned char* w_p= &(win_mess[0]);
unsigned char dummy = 0x00;
 
void Tick(){          
    
        switch(state){
            case RESTART:
                score = 0;
                win_b = 0x00;
                p_s = BD;
                dummy = 0x00;
                button = 0x00;
                is_paused = 0xFF;
                released = 0xFF;
                
                LCD_Cursor(1);
                LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_WriteData(score + '0');
                PORTB = 0x02;
                PORTA = 0x00;
            break;
            case BD:
            if(released){
                is_paused = ~is_paused;
                
                if(is_paused){
                if(prev == TWO) {score++;}
                else {if(score > 0) score--;} 
                LCD_Cursor(1);
                LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_WriteData(score + '0');
                //PORTB = 0x00;
               }                
            }        
            break;
            case PAUSE:
            ;
            break;
            case ONE:
                PORTB = 0x01;
            break;
            case TWO:
                PORTB = 0x02;
            break;
            case THREE:
                PORTB = 0x04;
            break;
            case WIN:
                if(!win_b){
                LCD_Cursor(1);
                LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_DisplayString(1, w_p);
                win_b = 0x10;
                p_s = RESTART;
                dummy = 0x01;
                }                
                tmpB = PORTB;
                PORTB = (tmpB ^ 0x07);                
            break;
            default:
            PORTB = 0x05;
            break;
        }
    
    switch(state){
        case RESTART:
            state = THREE; prev = THREE; next = THREE;
        break;
        case BD:
            if(is_paused){
                state = PAUSE;
                PORTB = 0x05;
            }else {state = ONE; prev = ONE; next = ONE;}   
                
            if(score == 9){state = WIN;};         
        break;
        case PAUSE:
            ;
        break;
        case ONE:
            prev = ONE;
            state = TWO;
            next = TWO;
        break;
        case TWO:
            if( prev == ONE ){
                state = THREE;
                next = THREE;
            }
            else {
                state = ONE;
                next = ONE;
            }
            prev = TWO;
        break;
        case THREE:
            prev = THREE;
            state = TWO;
            next = TWO;
        break;
        case WIN:
        //button = PINA & 0x01;
            if(button){state = RESTART; button = 0x00;}
        break;
        default:
        PORTB = 0x06;
        break;
        }
    released = 0x00;
} 
    
int main(void)
{   
    DDRA = 0x00; PORTA = 0x00; 
    DDRB = 0xFF; PORTB = 0x00; 
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    
    LCD_init();    
    TimerSet(period);
    TimerOn();
    
    button = 0x00; 
    pressed = 0x00;
    released = 0xFF;
    is_paused = 0x00;
    score = 5;
    
    LCD_Cursor(1);
    LCD_ClearScreen();
    LCD_Cursor(1);
    LCD_WriteData(score + '0');
    
    state = ONE;
    prev = ONE;
    p_s = BD;
    
    /* Replace with your application code */
        while(1){
            Tick();          
            while(!TimerFlag){
                        button = (PINA & 0x01);
                        if(button){
                            state = p_s;//BD;
                            button = dummy;
                        }else released = 0xFF;
            }          
            TimerFlag = 0; 
        }
       return 0;
}
