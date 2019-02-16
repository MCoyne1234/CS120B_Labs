/*
 * lab10_pt3.c
 *
 * Created: 2/12/2019 6:27:57 PM
 * Author : ashle
 */ 

#include <avr/io.h>
#include "timer.h"

enum States0 {zeroToOne, oneToOne, twoToOne} leds3_state;
enum States1 {off, on} blink_state;
enum States2 {combine} combine_state;
enum States3 {off1, play} button_state;
    
unsigned char temp_a, freq;	
unsigned char threeLeds = 0x00;
unsigned char blinkLed = 0x00;
unsigned char buzzer = 0x00;     
void Tick(){

	static int count = 0;
	static int count_blink = 0; 
	static int count_buzzer = 0; 
    static int count_button = 0;
	if(temp_a = PINA & 0x07){
        ++count_button;
    }else count_button = 0; 
    
    
    //unsigned char temp_b = 0x00;
    
	switch(leds3_state){ // 3 LEDs in sequence
		case zeroToOne:
			//if(threeLeds == 0x00){
			threeLeds = 0x01; //set only bit0 to 1
			if(count == 300){ //wait till 300 ms to switch to next state
				leds3_state = oneToOne;
			}
			break; 
		case oneToOne:
			//if(threeLeds == 0x02)
			threeLeds = 0x02; //set bit1 to 1
			if(count == 300){ //wait till 300 ms to switch to next state
				leds3_state = twoToOne;
			}
			break;
		case twoToOne:
			threeLeds = 0x04; //set bit2 to 1
			if(count == 300){ //wait till 300 ms to switch to next state
				leds3_state = zeroToOne;
			}
			break;
		default: leds3_state = zeroToOne; 
	}
	
	//second state machine
	switch(blink_state){
		case off:
			blinkLed = 0x00; 
			if(count_blink == 1000){ //wait till  ms to switch to next state
				blink_state = on; 
			}
			break;
		case on:
			blinkLed = 0x08;
			if(count_blink == 1000){ //wait till  ms to switch to next state
				blink_state = off; 
			}
			break; 
		default: 
			blink_state = off; 
	}
	switch(button_state){
		case off1:
            if( (temp_a & 0x01) && (count_button == 10) ){
                ++freq;
            }else if( (temp_a & 0x02 && (count_button == 10)) && (freq > 1) ){
                --freq;
            }
		    else if(temp_a & 0x04){
			    button_state = play;       
                 //buzzer = (buzzer ^ 0x10);
            }else buzzer = 0x00; 
		break;
		case play:
		///* 
            if ( (temp_a & 0x04) == 0x00 ){ button_state = off1; buzzer = 0x00; }
            else if((count_buzzer == freq) && ( (temp_a & 0x04) == 0x04)){
			    buzzer = (buzzer^0x10); //xor 
		    }
        //*/
		break;
		default: 
		break;
	}
	//now time to combine these SM 
	switch(combine_state){
		case combine:
            //if ( (temp_a) == 0x00 ){ buzzer = 0x00; }
			PORTB = (threeLeds | blinkLed | buzzer); // (or) these together
		break; 
		default:
			combine_state = combine;
	}
	
	if(count < 300 ){
		count++; //increase count 
	}
	else{
		count = 0;
	}
	if(count_blink < 1000){
		count_blink++;
	}
	else{
		count_blink = 0; 
	}
	if(count_buzzer < freq){
		count_buzzer++;
	}
	else{
		count_buzzer = 0; 
	}
}

int main(void)
{
    DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1); //set timer to 1 ms
	TimerOn();   //turn timer on 
	TimerFlag = 0;
	//set states
	leds3_state = zeroToOne;
	blink_state = off; 
	combine_state = combine;
    freq = 2;
    /* Replace with your application code */

    while (1) 
    {
		Tick();
		//we need this bc each SM is on a diff period 
		while(!TimerFlag){}; 
		TimerFlag = 0; 
    }
}



