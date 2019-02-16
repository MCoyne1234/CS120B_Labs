/*
 * lab10_pt5.c
 *
 * Created: 2/16/2019 12:29:35 AM
 * Author : Administrator
 */ 

#include <avr/io.h>
#include "timer.h"

enum StatesLED{WAIT, INC, DEC, RESET} stateLED;
unsigned char tempA, output, buttonRead = 3;
unsigned long buttonCount;

void Tick(){
    tempA = (PINA & 0x03);
    
    if(tempA){
        ++buttonCount;
    }else { buttonCount = 0;}
    
    switch(stateLED){
        case WAIT:
        break;
        case  INC:
            if( (output < 9) && tempA && (buttonCount >= buttonRead) && (buttonCount < 3000) && (buttonCount % 1000 == 0)){
                ++output;
            }else if( (output < 9) && tempA && (buttonCount >= buttonRead) && ( buttonCount == 3400) ){
                ++output;
                buttonCount = 3000;
            }else if( (output < 9) && tempA && buttonCount == buttonRead ) ++output;
        break;
        case DEC:
            if((output > 0) && tempA && (buttonCount >= buttonRead) && (buttonCount < 3000) && (buttonCount % 1000 == 0)){
                --output;
            }else if( (output > 0) && tempA && (buttonCount >= buttonRead) &&  (buttonCount == 3400) ){
                --output;
                buttonCount = 3000;
            }else if( (output > 0) && tempA && buttonCount == buttonRead ) --output;
        break;
        case RESET:
            output = 0x00;
        break;
    }
    
    switch(stateLED){
        case WAIT:
            if(tempA == 0x01){
                stateLED = INC;
            }else if(tempA == 0x02){
                stateLED = DEC;
            }else if(tempA == 0x03){
                stateLED = RESET;
            }
        break;
        case INC:
             if(tempA == 0x01){
                 stateLED = INC;
             }else stateLED = WAIT;
        break;
        case DEC:
            if(tempA == 0x02){
                stateLED = DEC;
            }else stateLED = WAIT;
        break;
        case RESET:
        if (!tempA) stateLED = WAIT;
        break;
    }  
    PORTB = output;
    //PORTB = 0x0F;
}

int main(void)
{
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    
    TimerSet(1);
    TimerOn();
    TimerFlag = 1;
    
    stateLED = WAIT;
    output = 1;
    /* Replace with your application code */
    while (1) 
    {
        Tick();
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

