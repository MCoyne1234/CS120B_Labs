/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 4 Exercise # 4
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>

enum States {INIT, LISTEN, HASH, Y_P, RELOCK} state; 
enum Debug {DB_INIT, DB_LISTEN, DB_HASH, DB_Y_P, DB_RELOCK} dbg; 
unsigned char tmpA, tmpB;

void Tick(){
    switch (state){
        case INIT :
            PORTB = 0x00;
            dbg = DB_INIT;
            PORTC = dbg;
        break;
        case LISTEN :
            dbg = DB_LISTEN;
            PORTC = dbg;
        break;
        case HASH :
            dbg = DB_HASH;
            PORTC = dbg;
        break;
        case Y_P :
            tmpB = PORTB;
            //PORTB = (tmpB & 0x01) ? (tmpB & 0xFE) : (tmpB | 0x01);
            PORTB = (tmpB ^ 0x01);
            dbg = DB_Y_P;
            PORTC = dbg;
        break;
        case RELOCK :
            PORTB = 0x00;
            dbg = DB_INIT;
            PORTC = dbg;
        break;
        default:
        //error
        break;
    }
    
    tmpA  = PINA;
        switch (state){
            case INIT :
                state = LISTEN;
            break;
            case LISTEN :
                if( (tmpA & 0x07) == 0x04){
                    state = HASH;
                }else if( (tmpA & 0x80) ){
                    state = RELOCK;
                }
            break;
            case HASH :
                if(tmpA && (tmpA & 0x07) == 0x02){
                    state = Y_P;
                }else { state = LISTEN; }
            break;
            case Y_P :
                state = LISTEN;
            break;
            case RELOCK :
                    state = HASH;
            break;
            default:
            //error
            break;
        }
}
    
int main(void)
{
    DDRA = 0x00;
    DDRB = 0xFF;
    PORTB = 0x00; 
     
    while (1) Tick();
    return 0; //shouldn't hit.
}



