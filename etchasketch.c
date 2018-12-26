/*---Etch a Sketch Game---*/

#include "game_console.h"
#include "function_prototypes.h"
#include "character.h"

//Frame Buffer 
extern byte frame_buffer[MAX_PAGE][MAX_COL];
//Button Register
extern volatile byte buttonFlag;  

void etchASketch(){
	//Print Etch Opening Screen
	printEtchOpening();
	
	//Clear Whole Screen
	wholeScreen(CLEAR, PAGEOFF);
	
	//Initialize Game Parameters
	byte page = 0;
	byte column = INIT_COL;
	byte row = INIT_ROW;
	byte pixel = 0;

	//Button Flag to 0
	buttonFlag = OFF;
	
	//Always Runs when etchASketch is called
	while(GAME_LOOP){
		
		//When External Interrupt turns Flag On
		if(buttonFlag){
			if(UP_BUTTON){
				row--;
				if(row<1){ //Guard to not overflow upwards
				row=1;
				}
			}
			if(DOWN_BUTTON){
				row++;
				if(row>MAX_ROW-1){ //Guard to not overflow downwards
					row=MAX_ROW-1;
				}
			}
			if(LEFT_BUTTON){
				column--;
				if(column<1){ //Guard to not overflow to left
					column=1;
				}
			}
			if(RIGHT_BUTTON){
				column++;
				if(column>MAX_COL-1){ //Guard to not overflow to right
					column=MAX_COL-1;
				}
			}
			//Clears Screen and Frame Buffer
			if(ACT1_BUTTON){
				clearFrameBuffer();
				wholeScreen(CLEAR, PAGEOFF);
				//Set Pixel Back to Center Once Cleared
				row = INIT_ROW;
				column = INIT_COL;
			}
			//Return to Main Menu
			if(ACT2_BUTTON){
				//Clear Junk in Frame Buffer
				clearFrameBuffer();
				//Clear Screen
				wholeScreen(CLEAR, PAGEOFF);
				break;	
			}
		}
		
		//Drawing Pixels Onto LCD Screen Based on new values of ROW and COLUMN
		page = row/8; 
		pixel = row%8;
		select_page(page);
		select_column(column);
		//Add this new pixel to the page
		pixel = (_BV(pixel)|(frame_buffer[page][column]));
		//Add New Pixel to Frame Buffer
		frame_buffer[page][column] = pixel;
		//Transmit New Pixel Draw Location to LCD
		LCD_tx(pixel, DATA);
		_delay_ms(20);
	}	
}
