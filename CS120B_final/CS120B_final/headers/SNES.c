// PORTA# just resolves to 0-7; 
#define SNES_CLOCK  PORTA0 
#define SNES_LATCH  PORTA1
#define SNES_DATA   PORTA2
#define SNES_PORT   PORTA
#define SNES_PIN    PINA

#define SNES_NONE        0
#define SNES_R          16
#define SNES_L         	32 
#define SNES_X          64 
#define SNES_A         128 
#define SNES_RIGHT     256   
#define SNES_LEFT      512  
#define SNES_DOWN     1024 
#define SNES_UP       2048 
#define SNES_START    4096 
#define SNES_SELECT   8192   
#define SNES_Y       16384  
#define SNES_B       32768  

#define OUTPUT_PORT PORTC
//SNES 13-16 not used, so bits 0-3 not used.

void SNES_init(){
    SNES_PORT |= (0x01 << SNES_CLOCK);
    SNES_PORT |= (0x01 << SNES_LATCH);
}

unsigned short SNES_Read(){
    unsigned short snes_pressed = 0x0000;
      
    // Turn latch on and off. Send signal to SNES controller 
      
    // FROM JChristy, Part 5:   
    /* 
        Every 16.67ms (or about 60Hz), the SNES CPU sends out a 12us wide, positive
        going data latch pulse on pin 3. This instructs the ICs in the controller
        to latch the state of all buttons internally.  
    */
	//SNES_PORT &= ~(0x01 << SNES_LATCH);
    SNES_PORT |= (0x01  << SNES_LATCH);
	SNES_PORT |= (0x01 << SNES_CLOCK);
    SNES_PORT &= ~(0x01 << SNES_LATCH);
    
    // FROM JChristy, Part 5 and 6:
    /*
        Each button on the controller is assigned a specific id which corresponds
        to the clock cycle during which that button's state will be reported.
        The table in section 6.0 lists the ids for all buttons. Note that
        multiple buttons may be depressed at any given moment. Also note
        that a logic "high" on the serial data line means the button is NOT
        depressed.
    */
    
    snes_pressed = (((~SNES_PIN) & (0x01 << SNES_DATA)) >> SNES_DATA);
    
    // For 16 clock cycles the controller outputs the keys pressed, 
	// but first one is a bit different and some not used.
	// See JChristy Part 6. 
    for(int i = 0; i < 16; i++){
        SNES_PORT &= ~(0x01 << SNES_CLOCK);
        snes_pressed <<= 1;
        snes_pressed |= ( ( (~SNES_PIN) & (0x01  << SNES_DATA) ) >> SNES_DATA);      
		SNES_PORT |= (0x01 << SNES_CLOCK);
    }
    return snes_pressed;
}

