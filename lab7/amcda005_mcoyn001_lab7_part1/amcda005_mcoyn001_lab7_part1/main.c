/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 7 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
*/

#include <avr/io.h>
#include "io.c"
#include "timer.h"

enum States{START, LISTEN, INC, DEC} state, prev, next;
unsigned char count, timer_cnt, button, pressed, tmpA, tmpB;

void Tick(){
      
    switch(state){
        case START:
            LCD_ClearScreen();
            LCD_Cursor(1);
            count = 0;      
            LCD_WriteData(count + '0');
               
        break;
        case LISTEN:
            if(!tmpA) { timer_cnt = 0; }
        break;
        case INC:
            if( (count < 9) && !(timer_cnt) ){
                count++;
                LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_WriteData(count + '0');
            }else if(timer_cnt == 900){ timer_cnt = 0;}           
             timer_cnt+=100;
        break;
        case DEC:
            if( (count > 0) && !(timer_cnt) ){
                count--;
                LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_WriteData(count + '0');           
            }else if(timer_cnt == 900){ timer_cnt = 0;}   
            timer_cnt+=100;
        break;
        default:
        break;
    }
    
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
}


int main(void)
{
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    
    DDRA = 0x00; PORTA = 0x00; // PORT A0+A1 buttons
    
    // Initializes the LCD display
    LCD_init();   
    // Starting at position 1 on the LCD screen, writes Hello World
    //LCD_DisplayString((unsigned char)1, "0");
    LCD_WriteData(0 + '0');
    TimerSet(100);
    TimerOn();
    TimerFlag = 0;
    count = 0;
    timer_cnt = 0;
    state = START;
    
    while(1) {
        Tick();
        while(!TimerFlag){ tmpA = PINA; }
        TimerFlag = 0;
        }
}

