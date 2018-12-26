/*----SPI----*/
//SPI functions

#include "game_console.h"
#include "function_prototypes.h"

//Initialize Microcontroller as Master 
void init_Master(){
	//Set MOSI and SCK as Outputs from MicroController
	SCK_DIR(OUT); 	
	MOSI_DIR(OUT); 	
	
	//Set MISO as Input to MicroController	
	MISO_DIR(IN); 	
	
	//Avoid Micro from being slave by setting SS pin as Output 
	SS_DIR(OUT);
	//Drive it to High to avoid micro being slave
	SS(ON);

	// SPI Control Register: SPCR
	//---Disabling SPI Interrupts: SPIE = 0
	//---Enable SPI: SPE = 1
	//---Data Order: MSB->LSB : DORD = 0 (according to LCD specifications)
	//---Master Select: MSTR = 1
    //---Clock Polarity, SCK LOW when idle: CPOL = 0
	//---Clock Phase, Data Sampled on Leading Edge: CPHA = 0
	//---Clock Freq = clk/4: (SPR1,SPR0) = (0,0)
	SPCR = _BV(SPE)|_BV(MSTR);	
}

//Sending Data from Master to Slave, 
byte SPI_Exchange(byte data){
	
	/* Start transmission */
	//SPI Data Register: SPDR
	SPDR = data; //Load Data Into Data Buffer
	
	//Conitnuosly Loop until Transmission is Complete
	//SPI Status Register: SPSR
	/*  1) When transfer starts, SPIF = 0,
		2) 1<<SPIF = 1000_0000 (this isolates the 7th bit of SPSR)
		3) !(SPSR&(1<<SPIF)) will have two states
			-->Transmission: !(SPSR&(1<<SPIF)) = !(0&1)(looking at 7th bit) = !(0) = 1
			-->Finished : !(SPSR&(1<<SPIF) = !(1,1)(looking at 7th bit) = !(1) = 0 
		4) Loop exits as condition is now zero */
	while(!(SPSR & (1<<SPIF)));
	
	//Return the succesfully transmitted data (if needed)
	return SPDR;
}


