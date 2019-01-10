/*    Partner(s) Name & E-mail:Ashley McDaniel amcda005@ucr.edu & Matthew Coyne mcoyn001@ucr.edu
 *    Lab Section: 022
 *    Assignment: Lab # 2 Exercise # 2
 *    Exercise Description: [optional - include for your own benefit]
 *      The program will assign A input value to B and so on.
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	// Initialize output on PORTB to 0x00
	unsigned char temp_input = 0x00;
	while(1)
	{
		temp_input = PINA;
		PORTB = temp_input;    // Writes port B's 8 pins with the values
		// on port A's 8 pins
	}


