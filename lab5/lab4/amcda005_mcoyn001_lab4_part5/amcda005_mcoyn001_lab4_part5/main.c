/*/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 4 Exercise # 5
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>

enum States {INIT, LISTEN, LOOP, Y_P, RELOCK} state; 
enum Debug {DB_INIT, DB_LISTEN, DB_LOOP, DB_Y_P, DB_RELOCK} dbg; 
enum Code {ZERO, X, Y, IGNORETHIS, HT} code[] = {HT,X,Y,X};
unsigned char tmpA, tmpB, count;;

//unsigned char[] code = {4,1,2,1}

void Tick(){
    switch (state){
        case INIT :
            PORTB = 0x00;
            count = 0;
            tmpA = 0x00;
            tmpB = 0x00;
            dbg = DB_INIT;
            PORTC = dbg;
        break;
        case LISTEN :
            count = 0;
            dbg = DB_LISTEN;
            PORTC = dbg;
        break;
        case LOOP :
            ++count;
            dbg = DB_LOOP;
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
                    state = LOOP;
                }else if( (tmpA & 0x80) ){
                    state = RELOCK;
                }
            break;
            case LOOP :
                if(count == 4){
                    state = Y_P;
                }else if(tmpA != code[count]) { state = LISTEN; }
            break;
            case Y_P :
                state = LISTEN;
            break;
            case RELOCK :
                    state = LOOP;
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