/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 9 Exercise # 3
 *    Exercise Description: [optional - include for your own benefit]
 *      Change LED lights when a button is pressed. 
 *      Consider more transitions to capture long presses? The simple solution has poor behavior. 
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

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


enum States {OFF, PLAY} state;
unsigned short system_period = 80; // 1/16th of a second is 62.5 ms, just round to 63;
//unsigned char bpm = 120; // 2 beats per second
//unsigned char bpm = 60; // Let's start with 1 beat per second to make it easy and adjust later maybe.
unsigned char eigth = 2 ; // ticks per note
unsigned char quarter = 6; // ticks per note 
unsigned char half = 8; // ticks per note 
unsigned char whole = 16;

double c4 = 261.63;
double d4 = 293.66;
double e4 = 329.63;
double f4 = 349.23;
double g4 = 392.00;
double a4 = 440.00;
double b4 = 493.88;
double c5 = 523.25;
double d5 = 587.33;
double e5 = 659.25;
double f5 = 698.46;
double g5 = 783.99;

unsigned char notes_number = 20;
unsigned char position = 0, count = 0;

void Tick()
{
    double music_notes[] = {d4,0.0,d4,0.0,d4,g4,d5,c5,b4,a4,g5,d5,c5,b4,a4,g5,d5,c5,b4,c5,a4};
    unsigned char note_length[] = {eigth,1,eigth,1,eigth,half,half,eigth,eigth,eigth, half, quarter, eigth,eigth,eigth, half, quarter, eigth,eigth,eigth,whole};

    unsigned char tempA = (~PINA & 0x01);
    
    switch(state)
    {
        case OFF:
        if(tempA == 0x01){
            state = PLAY;
        }
        else{
            state = OFF;
        }
        break;
        case PLAY:
        if( (position >=notes_number) && (count >= note_length[position])){
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
            count = 0;
            position = 0;
        break;
        case PLAY:
            if(count < note_length[position]){
                set_PWM(music_notes[position]);
            }else {
                position++;
                count = 0;
                set_PWM(music_notes[position]);              
            }     
            count++;                      
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
    
    TimerSet(system_period);
    TimerOn();
    
    state = OFF;
    TimerFlag = 0;
    count = 0;
    position = 0;
    while (1)
    {
        Tick();
         // Input is reversed to be activated on low, so we need to bitwise inverse PINA to get the same kind of logic as usual.
        while(!TimerFlag);
        TimerFlag = 0;       
    }
    return 0;
}
