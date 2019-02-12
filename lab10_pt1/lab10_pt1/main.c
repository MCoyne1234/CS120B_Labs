/*
 * lab10_pt1.c
 *
 * Created: 2/12/2019 1:19:14 PM
 * Author : ashle
 */ 

#include <avr/io.h>
#include "timer.h"

enum States0 {zeroToOne, oneToOne, twoToOne} leds3_state;
enum States1 {off, on} blink_state;
enum States2 {combine} combine_state;

void Tick(){
	unsigned char threeLeds = 0x00;
	unsigned char blinkLed = 0x00; 
	static int count = 0;
	
	switch(leds3_state){ // 3 LEDs in sequence
		case zeroToOne:
			//if(threeLeds == 0x00){
			threeLeds = 0x01; //set only bit0 to 1
			if(count == 1000){ //wait till 1000 ms to switch to next state
				leds3_state = oneToOne;
			}
			break; 
		case oneToOne:
			//if(threeLeds == 0x02)
			threeLeds = 0x02; //set bit1 to 1
			if(count == 1000){ //wait till 1000 ms to switch to next state
				leds3_state = twoToOne;
			}
			break;
		case twoToOne:
			threeLeds = 0x04; //set bit2 to 1
			if(count == 1000){ //wait till 1000 ms to switch to next state
				leds3_state = zeroToOne;
			}
			break;
		default: leds3_state = zeroToOne; 
	}
	
	//second state machine
	switch(blink_state){
		case off:
			blinkLed = 0x00; 
			if(count == 1000){ //wait till 1000 ms to switch to next state
				blink_state = on; 
			}
			break;
		case on:
			blinkLed = 0x08;
			if(count == 1000){ //wait till 1000 ms to switch to next state
				blink_state = off; 
			}
			break; 
		default: 
			blink_state = off; 
	}
	
	//now time to combine these SM 
	switch(combine_state){
		case combine:
			if(count == 1000){ //wait till 1000 ms to switch to next state
				PORTB = (threeLeds | blinkLed); // (or) these together
			}
			break; 
		default:
			combine_state = combine;
	}
	if(count < 1000){
		count++; //increase count 
	}
	else{ count = 0;}
}

int main(void)
{
	DDRB = 0xFF; 
	TimerSet(1); //set timer to 1 ms
	TimerOn();   //turn timer on 
	TimerFlag = 0;
	//set states
	leds3_state = zeroToOne;
	blink_state = off; 
	combine_state = combine;
    /* Replace with your application code */

    while (1) 
    {
		Tick();
		//we need this bc each SM is on a diff period 
		while(!TimerFlag){}; 
		TimerFlag = 0; 
    }
}

