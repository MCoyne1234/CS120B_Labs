

#include <avr/io.h>
#include "timer.h"


// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
    static double current_frequency; // Keeps track of the currently set frequency
    // Will only update the registers when the frequency changes, otherwise allows
    // music to play uninterrupted.
    if (frequency != current_frequency) {
        if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
        else { TCCR0B |= 0x03; } // resumes/continues timer/counter
        
        // prevents OCR3A from overflowing, using prescaler 64
        // 0.954 is smallest frequency that will not result in overflow
        if (frequency < 0.954) { OCR0A = 0xFFFF; }
        
        // prevents OCR0A from underflowing, using prescaler 64                    // 31250 is largest frequency that will not result in underflow
        else if (frequency > 31250) { OCR0A = 0x0000; }
        
        // set OCR3A based on desired frequency
        else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

        TCNT0 = 0; // resets counter
        current_frequency = frequency; // Updates the current frequency
    }
}

void PWM_on() {
    TCCR0A = (1 << COM0A0) | (1 << WGM00);
    // COM3A0: Toggle PB3 on compare match between counter and OCR0A
    TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
    // WGM02: When counter (TCNT0) matches OCR0A, reset counter
    // CS01 & CS30: Set a prescaler of 64
    set_PWM(0);
}

void PWM_off() {
    TCCR0A = 0x00;
    TCCR0B = 0x00;
}


enum States {OFF, NOTE_C4, NOTE_D4, NOTE_E4, HOLD}state;
double c4 = 261.63; 
double d4 = 293.66;
double e4 = 329.63;

void Tick()
{
    unsigned char tempA = (~PINA & 0x07);
    
    switch(state)
    {
        case OFF:
            if(tempA == 0x01){
                state = NOTE_C4;
            }
            else if(tempA == 0x02){
                state = NOTE_D4;
            }
            else if(tempA == 0x04){
                state = NOTE_E4;
            }
            else{
                state = OFF;
            }
        break;
        case NOTE_C4:
            if(tempA == 0x01){
                state = NOTE_C4;
            }else{
                    state = OFF;
            }
        break;
        case NOTE_D4:
        if(tempA == 0x02){
            state = NOTE_D4;
        }else{
            state = OFF;
        }
        break;
        case NOTE_E4:
            if(tempA == 0x04){
                state = NOTE_E4;
            }else{
                state = OFF;
            }
        break;
        default:
        state = OFF;
        break;
    }
    
    switch(state)
    {
        case OFF:
        set_PWM(0);
        break;
        case NOTE_C4:
        set_PWM(c4);
        break;
        case NOTE_D4:
        set_PWM(d4);
        break;
        case NOTE_E4:
        set_PWM(e4);
        break;
        case HOLD:
        set_PWM(0);
        break;
        default:
        set_PWM(0);
        break;
    }
}

int main()
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    
    PWM_on();
    set_PWM(0);    
    
    state = OFF;
    TimerFlag = 0;
    //unsigned char tempA;
    while (1)
    {      
        Tick();
//         tempA = ~PINA; // Input is reversed to be activated on low, so we need to bitwise inverse PINA to get the same kind of logic as usual. 
//         if( (tempA & 0x01) == 0x01){
//             set_PWM(440.00);
//             PORTD = 0xFF;
//         }      
//        while(!TimerFlag);
//        TimerFlag = 0;  
  
    }
    return 0;
}
