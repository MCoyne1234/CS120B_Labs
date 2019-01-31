/*
 * throwaway.c
 *
 * Created: 1/27/2019 7:50:47 PM
 * Author : Administrator
 */ 

#include <avr/io.h>


int main(void)
{   
    DDRA = 0x00;
    DDRB = 0xFF;
    PORTB = 0x00;
    /* Replace with your application code */
    while (1) 
    {
        PORTB = PINA;
    }
}

