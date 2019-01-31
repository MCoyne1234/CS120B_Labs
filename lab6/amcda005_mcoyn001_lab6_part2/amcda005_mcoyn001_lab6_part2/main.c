/*/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 6 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 
#include <avr/io.h>
#include <timer.h>

enum States{ PAUSE, ONE, TWO, THREE} state, prev;
unsigned char button;
 
 
void Tick(){
     
    switch(state){
        case PAUSE:
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
        default:
        break;    
        }
     
    button = PINA;
    switch(state){
        case PAUSE:
           if(button) state = ONE;
        break;
         case ONE:
           prev = ONE;
           if(button) state = PAUSE; 
           else state = TWO;
        break;
        case TWO:
        if(button) state = PAUSE;
        else {
            if( prev == ONE ) state = THREE;
            else state = ONE;
        }            
            prev = TWO;
        break;
        case THREE:
            if(button) state = PAUSE;
            else prev = THREE;
           state = TWO;
        break;
        default:break;
    }
}     
int main(void)
{   
    DDRA = 0x00;
    DDRB = 0xFF;
    DDRC = 0x00;
    DDRD = 0x00;
    
    PORTB = 0x00;
    
    TimerSet(300);
    TimerOn();
    
    button = 0;
    state = ONE;
    prev = ONE;
    /* Replace with your application code */
        while(1){
            Tick();
            while(!TimerFlag){};          
            TimerFlag = 0; 
        }
       return 0;
}
