/*
 * centipede_game.c
 *
 * Created: 3/2/2019 7:28:03 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <SNES.c>
#include <timer.h>

int main(void)
{
    DDRA = 0x03; PORTA = 0x00; // input for SNES controller
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00; // output 
    DDRD = 0xFF; PORTD = 0x00;
    
    SNES_init();
    
    unsigned short button = 0x0000;
    unsigned char output = 0x00;
    while (1) 
    {
        output = 0x00;
        button = (SNES_Read());
        ///*
               // if((button & 1) == 1) output |= 0x0A;
                //if((button & 2) == 2) output |= 0xA0;
                if((button & 4) == 4) output |= 0xAA;
                if((button & 8) == 8) output |= 0xFF;
        if((button & 16) == 16) output |= 0x01;
        if((button & 32) == 32) output |= 0x02;
        if((button & 64) == 64) output |= 0x04;
        if((button & 128) == 128) output |= 0x08;
        if((button & 256) == 256) output |= 0x10;
        if((button & 512) == 512) output |= 0x20;
        if((button & 1024) == 1024) output |= 0x40;
        if((button & 2048) == 2048) output |= 0x80;
        if((button & 4096) == 4096) output |= 0x03;
        if((button & 8192) == 8192) output |= 0x06;
        if((button & 16384) == 16384) output |= 0x0C;
        if((button & 32768) == 32768) output |= 0x18;
        PORTD = output;
    }
}

