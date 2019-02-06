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
#include "io.h"
#include <io.c>


enum States{ PAUSE, BD, ONE, TWO, THREE, WIN} state, prev, next, p_s;
unsigned char button, pressed, released, is_paused, score;
unsigned long period = 300; // period before each transition is; 
const unsigned char win_mess[] = "You Win";
const unsigned char* w_p= &(win_mess[0]);
 
void Tick(){
          
        switch(state){
            case BD:
                score++;
                //if(score != 6){
                 //   state = WIN;
                   // PORTB = 0x07;
                //}else if (score < 4){state = WIN; PORTB = 0x05;}
                //if(prev == TWO) score++;
                //else score--;
            break;
            case PAUSE:

                if(released){
                    p_s = BD;
                    button = 0x00;
                    }
                else{p_s = PAUSE;}
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
                LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_DisplayString(1, w_p);
                PORTB = 0x07;
            break;
            default:
            break;
        }
        switch(state){
            case BD:
            //When button is pressed, figure out whether to Pause, or restart.
            if(!is_paused){
                state = PAUSE;
                is_paused = !is_paused;
            }else {
                state = ONE;
                is_paused = !is_paused;
            }
            break;
            case PAUSE:
                if(score >= 9){
                    state = WIN;
                    PORTB = 0x07;
                }else if (score < 0){}
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
                //if(button && released){state = ONE;}
            break;
            default:break;
        }
}     
int main(void)
{   
    DDRA = 0x00; PORTA = 0x00; 
    DDRB = 0xFF; PORTB = 0x00; 
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    
    TimerSet(period);
    TimerOn();
    
    button = 0x00; 
    pressed = 0x00;
    released = 0xFF;
    is_paused = 0x00;
    score = 5;
    
    state = ONE;
    prev = ONE;
    p_s = BD;
    
    LCD_ClearScreen();
    LCD_Cursor(1);
    LCD_WriteData(score + '0');
    /* Replace with your application code */
        while(1){
            Tick();
            while(!TimerFlag){
                pressed = PINA;
                if(pressed){ 
                    button = 0xFF;
                    released = 0x00;
                    state = p_s;
                    }else{released = 0xFF;}                 
             }          
            TimerFlag = 0; 
        }
       return 0;
}
