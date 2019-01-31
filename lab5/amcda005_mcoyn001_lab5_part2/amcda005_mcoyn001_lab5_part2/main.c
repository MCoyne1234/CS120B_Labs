/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 5 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>
enum States {INIT, START, TRAN,INC, DEC, RESET} state; 
unsigned char tmpA, tmpB;

void Tick(){
    tmpB = PORTB;
    switch (state){
        case INIT :
            PORTB = 0x01;
        case START :
            // Nothing.
        break;
        case INC :
            if( (tmpB < 9) ){
                PORTB = ++tmpB;
            }
        break;
        case DEC :
            if( (tmpB > 0) ){
                PORTB = --tmpB;
            }
        break;
        case RESET :
            PORTB = 0x00;
        break;
        case TRAN :
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
                if( (tmpA & 0x01) ){
                    state = INC;
                }else if( (tmpA & 0x02) ){
                    state = DEC;
                }else if( (tmpA & 0x03) == 0x03 ){
                    state = RESET;
                }
            break;
            case INC :
                if( ( (tmpA & 0x03) == 0x03))  {
                    state = RESET;
                }else {
                    state = TRAN;
                }                
            break;
            case DEC :
                if( ( (tmpA & 0x03) == 0x03) ){
                    state = RESET;
                }else {
                  state = TRAN;
                }
            break;
            case RESET :
                    state = START;
            break;
            case TRAN :
                if(!tmpA){
                    state = START;
                } else if( ( (tmpA & 0x03) == 0x03) ){
                    state = RESET;
                }
                tmpA = 0;
                    
            break;
            default:
            //error
            break;
        }
}
    
int main(void)
{
    DDRA = 0xFC;
    DDRB = 0xFF;
    PORTA = 0x00;
    PORTB = 0x01; 
    state = INIT;
    tmpA = 0;
     
    while (1) {
        Tick();
    }
    return 0; //shouldn't hit.
}

