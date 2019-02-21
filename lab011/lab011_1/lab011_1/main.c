/*
 * lab011_1.c
 *
 * Created: 2/19/2019 12:41:21 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <bit.h>
#include <timer.h>
#include <stdio.h>
#include <scheduler.h>


// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7
   col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/
unsigned char GetKeypadKey() {

    PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('1'); }
    if (GetBit(PINC,1)==0) { return('4'); }
    if (GetBit(PINC,2)==0) { return('7'); }
    if (GetBit(PINC,3)==0) { return('*'); }

    // Check keys in col 2
    PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('2'); }
    if (GetBit(PINC,1)==0) { return('5'); }
    if (GetBit(PINC,2)==0) { return('8'); }
    if (GetBit(PINC,3)==0) { return('0'); }
    // ... *****FINISH*****

    // Check keys in col 3
    PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    // ... *****FINISH*****
    if (GetBit(PINC,0)==0) { return('3'); }
    if (GetBit(PINC,1)==0) { return('6'); }
    if (GetBit(PINC,2)==0) { return('9'); }
    if (GetBit(PINC,3)==0) { return('#'); }

    // Check keys in col 4    
    // ... *****FINISH*****
    PORTC = 0x7F; // Enable col 6 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    // ... *****FINISH*****
    if (GetBit(PINC,0)==0) { return('A'); }
    if (GetBit(PINC,1)==0) { return('B'); }
    if (GetBit(PINC,2)==0) { return('C'); }
    if (GetBit(PINC,3)==0) { return('D'); }

    return('\0'); // default value

}


void KeypadTick(){
    unsigned char x;
    x = GetKeypadKey();
    switch (x) {
        case '\0': PORTB = 0x1F; break; // All 5 LEDs on
        case '1': PORTB = 0x01; break; // hex equivalent
        case '2': PORTB = 0x02; break;
        case '3': PORTB = 0x03; break;
        case '4': PORTB = 0x04; break;
        case '5': PORTB = 0x05; break;
        case '6': PORTB = 0x06; break;
        case '7': PORTB = 0x07; break;
        case '8': PORTB = 0x08; break;
        case '9': PORTB = 0x09; break;
        case 'A': PORTB = 0x0A; break;
        case 'B': PORTB = 0x0B; break;
        case 'C': PORTB = 0x0C; break;
        case 'D': PORTB = 0x0D; break;
        case '*': PORTB = 0x0E; break;
        case '0': PORTB = 0x00; break;
        case '#': PORTB = 0x0F; break;
        default: PORTB = 0x1B; break; // Should never occur. Middle LED off.
    }
}


int main(void)
{
    DDRA = 0xFF; PORTA = 0x00;
    //DDRB = 0x00; PORTB = 0x00;
    DDRC = 0x00; PORTB = 0x00; // PORTB set to output, outputs init 0s
    DDRD = 0xFF; PORTD = 0x00; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
    unsigned long keypad_time = 10;
    
    while(1) {
        
        }
    }

