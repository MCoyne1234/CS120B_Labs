/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 6 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 
#include <avr/io.h>
#include "timer.h"
#include "io.h"


enum States{ PAUSE, BD, ONE, TWO, THREE} state, prev, next, p_s;
unsigned char button, pressed, released, is_paused;
unsigned long period = 300; // period before each transition is; 

 
void Tick(){
          
        switch(state){
            case BD:
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
            default:break;
        }
}     
int main(void)
{   
    DDRA = 0x00; PORTA = 0x00; 
    DDRB = 0xFF; PORTB = 0x00; 
    
    TimerSet(period);
    TimerOn();
    
    button = 0x00; 
    pressed = 0x00;
    released = 0xFF;
    is_paused = 0x00;
    
    state = ONE;
    prev = ONE;
    p_s = BD;
    
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