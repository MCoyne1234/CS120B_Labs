/*
 * lab9part2.c
 *
 * Created: 2/7/2019 6:54:17 PM
 * Author : ashle
 */ 
/*
 * lab9part1.c
 *
 * Created: 2/7/2019 5:11:17 PM
 * Author : ashle
 */ 

#include <avr/io.h>
#include "timer.h"

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
	TCCR0A = (1 << COM0A0)|(1 << WGM00);
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

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
unsigned char temp_a, temp_b, count;
unsigned char press = 0;

//double c4 = 261.63, d4 = 293.66, e4 = 329.63; //global variables :(

enum States { off, increase, decrease, buttonPress, playingNotes} state;
void Tick(){
	double notes [8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
	temp_a = PINA & 0x07;//reading input
	
	switch(state){	
		case off:
			if(temp_a == 0x02){
				if(count < 7){
					count ++; 
				}
				set_PWM(notes[count]);
				state = increase; 
			}
			else if (temp_a == 0x04){
				if(0 != count){
					count --;
				}
				set_PWM(notes[count]);
				state = decrease;
			}
			else{
				state = off; //do nothing because it is off
				//turn off buzzer
				set_PWM(0);
				PORTB = 0x00;
			}
			break; 
		case increase:
			if(temp_a == 0x02){
				if(count < 7){
					count ++;
				}
				set_PWM(notes[count]);
				state = increase;
			}
			else{
				state = off; 
			}
			
			break; 
		case decrease:
			if (temp_a == 0x04){
				if(0 != count){
					count --;
				}
				set_PWM(notes[count]);
				state = decrease;
			}
			else{
					state = off;
			}
				
			break;
		default: 
			state = off;
			break;
	}
	switch(state){
		case playingNotes:
			if(temp_a == 0x01){
				if(!press){
					state = buttonPress;
					PWM_on();
					set_PWM(notes[count]);
					//then set !press back to press
					press = 1; 
				}
				else{
					//turn the buzzer off 
					press = 0; 
					set_PWM(0);
					PORTB = 0x00;
					state = buttonPress;
				} 
			}
			else{
				state = playingNotes; 
			}
		case buttonPress:
			if(temp_a == 0x01){
				state = buttonPress;
			}
			else{
				state = playingNotes;
			}
			break;
        case increase:
        break;
		case decrease:
			if(temp_a == 0x04){
				if(!press){
					PWM_on();
					set_PWM(notes[count-1]);
					//then set !press back to press
					press = 1;
				}
				else{
					//turn the buzzer off
					press = 0;
					set_PWM(0);
					PORTB = 0x00;
				}
				
			}
		
		default:
			break;
	}
	/*
	if(temp_a){
		press = 1; //button has been pressed
	}
	else {
		press = 0;  //the button has not been pressed
	}*/
};

int main(void)
{
	DDRB = 0xFF; 
	DDRA = 0x00; 
	
	TimerSet(1);
	TimerOn();
	TimerFlag = 0;
	
	PWM_on();
	set_PWM(0);
    /* Replace with your application code */
    while (1) 
    {
		//c4 = 261.63 d4=293.66 e4=329.63
		Tick();
		/*
		if(temp_a == 0x01){
			set_PWM(c4);
			while(!TimerFlag){}
			TimerFlag = 0;
		}
		else if(temp_a == 0x02){
			set_PWM(d4);
			while(!TimerFlag){}
			TimerFlag = 0;
		}
		else if(temp_a == 0x04){
			set_PWM(e4);
			while(!TimerFlag){}
			TimerFlag = 0;
		}
		else{ //turn off buzzer
			set_PWM(0);
			PORTB = 0x00;
		}
		*/
	}
		
}

