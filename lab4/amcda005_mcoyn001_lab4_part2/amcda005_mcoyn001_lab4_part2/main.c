/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 4 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>
enum States {INIT, START, INC, DEC, RESET} state; 
unsigned char tmpA, tmpC;

void Tick(){
    tmpC = PORTC;
    switch (state){
        case INIT :
            PORTB = 0x00;
            PORTC = 0x07;
        break;
        case START :
            // Nothing.
        break;
        case INC :
            if(tmpA && (tmpC < 9) ){
                PORTC = ++tmpC;
            }
        break;
        case DEC :
            if( tmpA && (tmpC > 0) ){
                PORTC = --tmpC;
            }
        break;
        case RESET :
            PORTC = 0x00;
        break;
        default:
        //error
        break;
    }
    
    tmpA  = PINA;
        switch (state){
            case INIT :
                state = START;
            break;
            case START :
                if( (tmpA & 0x01) == 0x01){
                    state = INC;
                }else if( (tmpA & 0x02) ){
                    state = DEC;
                }else if( (tmpA & 0x03) == 0x03 ){
                    state = RESET;
                }
            break;
            case INC :
                if( ( (tmpA & 0x03) > 0x01))  {
                    state = RESET;
                }
            break;
            case DEC :
                if( tmpA && ( (tmpA & 0x03) != 0x02) ){
                    state = RESET;
                }
            break;
            case RESET :
                    state = START;
            break;
            default:
            //error
            break;
        }
}
    
int main(void)
{
    DDRA = 0x00;
    DDRC = 0xFF;
    PORTB = 0x07; 
     
    while (1) Tick();
    return 0; //shouldn't hit.
}

