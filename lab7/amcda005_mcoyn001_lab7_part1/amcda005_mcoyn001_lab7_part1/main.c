/*
 * amcda005_mcoyn001_lab7_part1.c
 *
 * Created: 1/31/2019 3:11:15 PM
 * Author : Administrator
 */ 


#include <avr/io.h>
#include "io.c"
#include "timer.h"

enum States{START, LISTEN, INC, DEC} state, prev, next;
unsigned char count, timer_cnt, button, pressed, tmpA, tmpB;

void Tick(){

        switch(state){
            case START:
                state = LISTEN;
            break;
            case LISTEN:
            if(tmpA == 0x01){
                state = INC;
            }else if (tmpA == 0x02){
                state = DEC;
            }
            else if (tmpA == 0x03){
                state = START;
            }
            break;
            case INC:
                if(tmpA == 0x03){
                    state = START;
                }else if (tmpA != 0x01){
                    state = LISTEN;
                }
            break;
            case DEC:
                if(tmpA == 0x03){
                    state = START;
                    }else if (tmpA != 0x02){
                    state = LISTEN;
                }
            break;
            default:
            break; 
        }
    
    
    switch(state){
        case START:
            count = 0;
            timer_cnt = 0;
        break;
        case LISTEN:
            timer_cnt = 0;
        break;
        case INC:
            if( (count < 9) && (timer_cnt % 1000 == 0) ){
                count++;
                timer_cnt = 0;
            }            
            timer_cnt += 100;
        break;
        case DEC:
            if( (count > 0) && (timer_cnt % 1000 == 0) ){
                count--;
                timer_cnt = 0;
            }
        timer_cnt += 100;
        break;
        default:
        break;
    }
    
}


int main(void)
{
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    
    DDRA = 0x00; PORTA = 0x00; // PORT A0+A1 buttons
    
    // Initializes the LCD display
    LCD_init();   
    // Starting at position 1 on the LCD screen, writes Hello World
    LCD_DisplayString(1, '0');
    TimerSet(100);
    TimerFlag = 0;
    while(1) {
        while(!TimerFlag){ tmpA = PINA; }
        }
        Tick();
        TimerFlag = 0;
        LCD_DisplayString(1, count + '0');
}

