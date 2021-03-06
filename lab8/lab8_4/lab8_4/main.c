/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 8 Exercise # 4
 *    Exercise Description: [optional - include for your own benefit]
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
//Exercise 4: Light Meter (Challenge)

#include <avr/io.h>
void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
    DDRB = 0xFF;
    DDRD = 0xFF;
    
	ADC_init();
	unsigned short adc_var = 0x0000;
	unsigned short max = (0x0180); // The
	unsigned short inc = (max)/8;		//replace with (max/8)
    while (1) 
    {
		adc_var = ADC;					//read ADC in variable
		
		if(adc_var > (inc*7)){
			//then turn on 8 LEDs
			PORTB = 0xFF;
		}
		else if(adc_var > (inc*6)){
			//then turn on 7 LEDs
			PORTB = 0x7F;
		}
		else if(adc_var > (inc*5)){
			//then turn on 6 LEDs
			PORTB = 0x3F;
		}
		else if(adc_var > (inc*4)){
			//then turn on 5 LEDs
			PORTB = 0x1F;
		}
		else if(adc_var > (inc*3)){
			//then turn on 4 LEDs
			PORTB = 0x0F;
		}
		else if(adc_var > (inc*2)){
			//then turn on 3 LEDs
			PORTB = 0x07;
		}
		else if(adc_var > (inc*1)){
			//then turn on 2 LEDs
			PORTB = 0x03;
		}
		else if(adc_var > (inc*0)){
			//then turn on 1 LEDs
			PORTB = 0x01;
		}
		else{
			PORTB = 0x00;
		}
    }
}

