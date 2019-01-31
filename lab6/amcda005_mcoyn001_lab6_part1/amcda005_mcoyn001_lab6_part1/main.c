/*/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 6 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 
#include <avr/io.h>
#include <timer.h>

 enum States{ START, ONE, TWO, THREE} state;
 
 
 void Tick(){
     
     switch(state){
         case START:
            PORTB = 0x00;
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
     
     switch(state){
         case START:
            state = ONE;
         break;
         case ONE:
            state = TWO;
         break;
         case TWO:
            state = THREE;
         break;
         case THREE:
            state = START;
         break;
         default:break;
     }
 }     
int main(void)
{   
    DDRB = 0xFF;
    PORTB = 0x00;
    
    TimerSet(1000);
    TimerOn();
    
    state = START;
    /* Replace with your application code */
        while(1){
            Tick();
            while(!TimerFlag){};          
            TimerFlag = 0; 
        }
       return 0;
}

