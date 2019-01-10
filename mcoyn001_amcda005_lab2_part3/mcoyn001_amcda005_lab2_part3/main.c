/*
 * mcoyn001_amcda005_lab2_part3.c
 *
 * Created: 1/10/2019 1:21:12 PM
 * Author : ashle
 */ 

#include <avr/io.h>

int main(void)
{
    DDRB = 0xFF; // Configure port B's 8 pins as outputs
    PORTB = 0x00; // Initialize PORTB output to 0?s
    //1 means car is parked in space
    //4 spaces
    unsigned char cntavail;	//spaces available counter
    
    DDRA = 0xF0;    // Configure port A's pins as outputs
    PORTB = 0x00;   // Initialize PORTB output to 0?s
    DDRC == 0xFF;
    PORTC = 0x00;   //init
    cntavail = 4;   //start off with 4 empty spaces,
    //want to output number of empty spaces
    unsigned char counter = 0x00;
    counter = PINA;
    while(1)
    {
        PORTB = 0x0F; // Writes port B's 8 pins with 00001111
        counter = cntavail;
        if(PINA & 0x01 == 0x00){}
        else{
            counter -= 1;
        }
        if(PINA & 0x02 == 0x00 ){}
        else{
            counter -= 1;
        }
        if(PINA & 0x04 == 0x00 ){}
        else{
            counter -= 1;
        }
        if(PINA & 0x08 == 0x00 ){}
        else{
            counter -= 1;
        }
        PORTC = counter; //write output
    }
}