/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 5 Exercise # 1
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
        DDRA = 0x00;
        DDRB = 0xFF;
        
        PORTA = 0x00;
        PORTB = 0x00;
        unsigned char tmpA; 
    
    while (1) 
    {
        tmpA = PINA;
        if (tmpA == 0 ){
            PORTB = (64);
        }
        else if (tmpA <= 2){
            PORTB = (32 + 64 );
        }
        else if(tmpA <=4){
            PORTB = (32 + 16 + 64);
        }
        else if(tmpA <= 6){
            PORTB = (32 + 16 + 8);
        }
        else if(tmpA <= 9){
            PORTB = (32 + 16 + 8 + 4);
        }
        else if(tmpA <= 12){
            PORTB = (32 + 16 + 8 + 4 + 2);
        }
        else if(tmpA <= 15){
            PORTB = (32 + 16 + 8 + 4 + 2 + 1);
        }

    }
}