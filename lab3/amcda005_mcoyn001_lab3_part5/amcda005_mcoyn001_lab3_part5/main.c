/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 3 Exercise # 5
 *    Exercise Description: [optional - include for your own benefit]
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
    DDRD = 0x00; PORTD = 0x00; // Init D to input;
    DDRB = 0xFE; PORTB = 0x00; // Init B with B[7-1] output, B0 input.

    unsigned short weight = 0x0000; // need 9 bits, so short is next smallest. 
    unsigned char tempD, tempB; // temps to read pins. 
    while (1) 
    {
        // Assign temps to pins.
        tempD = PIND;
        tempB = PINB;

        weight = (tempD << 1) | (tempB & 0x01); // copy D to weight[1-8] and B0 to weight0.
        if(weight >= 70) {
            tempB = (tempB | 0x02); // Turn on B1, preserve B0;
        }else if(weight > 5){
            tempB = (tempB & 0x01) | (0x04); // Turn on B2 and preserve B1, ensure B1 is zero.
        }else{
            tempB = (tempB & 0x01); // Turn B1 and B2 off, preserve B0;
        }
        PORTB = tempB; //write to B.
    }
}

