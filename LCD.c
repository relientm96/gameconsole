/*---LCD Functions----*/

#include "game_console.h"
#include "function_prototypes.h"

//Global Variables
//Frame Buffer to store active pixels
byte frame_buffer[MAX_PAGE][MAX_COL];

//Initialize LCD as slave
void init_LCD(){
	
	//Set Output Pins
	LCD_CD_DIR(OUT);	
	LCD_RST_DIR(OUT);	
	LCD_CS_DIR(OUT);
	
	//Initialize LCD
	
	//Reset LCD first
	LCD_RST(HIGH);
	_delay_ms(10);
	LCD_RST(LOW);
	_delay_ms(5);
	LCD_RST(HIGH);
	_delay_ms(10);
	
	//Perform Initializations on LCD using SPI Transmission
	LCD_tx(0x40,CMD);//Display start line 0
	LCD_tx(0xA1,CMD);//SEG reverse
	LCD_tx(0xC0,CMD);//Normal COM0~COM63
	LCD_tx(0xA4,CMD);//Disable -> Set All Pixel to ON
	LCD_tx(0xA6,CMD);//Display inverse off
	_delay_ms(120);
	LCD_tx(0xA2,CMD);//Set LCD Bias Ratio A2/A3
	LCD_tx(0x2F,CMD);//Set Power Control 28...2F
	LCD_tx(0x27,CMD);//Set VLCD Resistor Ratio 20...27
	LCD_tx(0x81,CMD);//Set Electronic Volume
	LCD_tx(0x10,CMD);//Set Electronic Volume 00...3F
	LCD_tx(0xFA,CMD);//Set Adv. Program Control
	LCD_tx(0x90,CMD);//Set Adv. Program Control x00100yz yz column wrap x Temp Comp
	LCD_tx(0xAF,CMD);//Display on
}

/*--General LCD Helper Functions--*/

//Perform Data Transmission to LCD
//Can be used for both Commands or Data (Depending on CD_mode)
void LCD_tx(byte tx_byte, byte CD_mode){
	//Pull CS' Low to select LCD
	LCD_CS(LOW); 
	//Determine if sending a command or data to LCD (from CD_mode)
	LCD_CD(CD_mode); 
	//Perform SPI data transmission with tx_byte as data
	SPI_Exchange(tx_byte);
	//Pull CS' High to deselect LCD
	LCD_CS(HIGH);
}

//Function to clear whole LCD screen
void wholeScreen(uint16_t load, byte clear){
	byte page;
	byte column;
	for(page=0;page<MAX_PAGE;page++){
		for(column=0; column<MAX_COL;column++){
			select_column(column);
			select_page(page);
			if (load==0){                                       
				//Load=0, clear=0: turn all pixels off
				//Send to LCD as 'data'
				LCD_tx(clear,DATA); 
			}
		}
	}
}

/*----For Etch A Sketch----*/
//Select page on LCD
void select_page (byte page){
	
	//Variable to store our new page address
	byte page_cmd_address;
	
	//Ensure we do not go out of bounds
	if( page > MAX_PAGE ) page = MAX_PAGE;
	
	//Setting desired page
	page_cmd_address =(CMD_PAGE | page);
	
	//Transmit page command address to LCD
	LCD_tx(page_cmd_address,CMD);
}

//Select column on LCD
void select_column(byte column){
	
	//Variables to store 
	//4 MSBs
	byte page_cmd_address_MSB;
	//4 LSBs
	byte page_cmd_address_LSB;
	
	//Setting desired column
	//0x0F = 0000_1111 in binary, as we 'AND' column with 0x0F, we only affect lower 4 bits
	//column>>4 shifts the column bits 4 times to the right
	page_cmd_address_LSB =(CMD_COL_LSB | (column & 0x0F));
	page_cmd_address_MSB =(CMD_COL_MSB | (column >> 4));
	
	//Send column command address to LCD
	LCD_tx(page_cmd_address_LSB,CMD);
	LCD_tx(page_cmd_address_MSB,CMD);
}

//Helper Function to clear Frame Buffer for new Sessions
void clearFrameBuffer(){
	byte page;
	byte column;
	for(page=0;page<MAX_PAGE;page++){
		for(column=0;column<MAX_COL;column++){
			//Clearing All Pixels from Frame Buffer
			frame_buffer[page][column] = OFF;
		}
	}
}


