/*/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 5 Exercise # 3
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>

enum States {INIT, LISTEN, LOOP, TRAN} state; 
enum Debug {DB_INIT, DB_LISTEN, DB_LOOP, DB_Y_P, DB_RELOCK} dbg; 
enum Code {ZERO = 0 , X = 1, Y = 5, IGNORETHIS = 11, HT = 15} code[] = {X,Y,X,Y, IGNORETHIS, HT, IGNORETHIS, HT};
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
        
        break;
        case LOOP :
            PORTB = code[count];
            ++count;
            if(count >=7){
                count = 0;
            }
            
        break;
        case TRAN:
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
                if( (tmpA) ){
                    state = LOOP;
                }
            break;
            case LOOP :
                state = LISTEN;
            break;
            case TRAN:
            if (!tmpA) state = LISTEN;
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

