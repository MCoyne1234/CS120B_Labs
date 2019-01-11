/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 2 Exercise # 3
 *    Exercise Description: [optional - include for your own benefit]
 *		The program will assign C the number of empty spaces represented as zeroes on A, extended to only affect lower nibble.
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
 
 
 #include <avr/io.h>

int main(void)
{
	//1 means car is parked in space
	//4 spaces
	unsigned char cntavail;	//spaces available counter
	
	DDRA = 0x00;    // Configure PORTA's pins as inputs
	PORTA = 0x00;   // Initialize PORTA 0s
	DDRC == 0xFF; 
	PORTC = 0x74;   // Set PORTC7 to '0', PORTC[4-6] to '1' (to test only lower nibble affected), PORTC[0-3] to 0100  
	cntavail = 4;   // Start off with 4 empty spaces, 
	
	//want to output number of empty spaces
	
	unsigned char counter = 0x00; 
	unsigned char lot_full = 0x80;
	unsigned char mask = 0x8F; // mask to change only the lower nibble AND bit 7 when lot is full
	
	while(1)
	{
		counter = cntavail;
		if( (PINA & 0x01) == 0x01){
			counter -= 1; 
		}
		if( (PINA & 0x02) == 0x02 ){
    		counter -= 1;
		}
		if( (PINA & 0x04) == 0x04 ){
    		counter -= 1;
		}
		if( (PINA & 0x08) == 0x08 ){
			counter -= 1;
		}
		
		//value = (value & ~mask) | (newvalue & mask);
		if(counter == 0){
			PORTC =  (PORTC & ~mask) | (lot_full & mask); // Lot is full, clear lower nibble and set PORTC7 to '1'
		}else{
			PORTC =  (PORTC & ~mask ) | (counter & mask); // Write value to lower nibble of PORTC and set PORTC7 to '0'
		}
	}
}

