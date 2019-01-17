/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 3 Exercise # 4
 *    Exercise Description: [optional - include for your own benefit]
 *      
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{    
    DDRA = 0x00; PORTA = 0x00; // init A to input.
    DDRB = 0xFF; PORTB = 0x00; // init B to output.
    DDRC = 0xFF; PORTC = 0x00; // init C to output.
    
    unsigned char tmpA = 0x00;
    
    while(1)
    {
         tmpA = PINA;
            PORTB = (tmpA >> 4);
            PORTC = (tmpA << 4 );
    }
    
    return 0;
}



