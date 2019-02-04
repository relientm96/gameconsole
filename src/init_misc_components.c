/*------Initialization Functions------*/

#include "game_console.h"

void initialize_LOWLED(){
	//Make sure it is off before changing direction
	BAT_LOW_LED(OFF); 
	
	//Set BATTERY LED I/Os as outputs.
	//This will cause this to be external interrupt pin as well 
	BAT_LOW_LED_DIR(OUT);
}

void initialize_Buttons(){
	//Activate Internal Pull Ups
	UP_BUTTON_SET(ON); 
	DOWN_BUTTON_SET(ON); 
	LEFT_BUTTON_SET(ON); 
	RIGHT_BUTTON_SET(ON); 
	ACT1_BUTTON_SET(ON); 
	ACT2_BUTTON_SET(ON); 

	//Set button pins as Input
	UP_BUTTON_DIR(IN); 
	DOWN_BUTTON_DIR(IN); 
	LEFT_BUTTON_DIR(IN); 
	RIGHT_BUTTON_DIR(IN); 
	ACT1_BUTTON_DIR(IN); 
	ACT2_BUTTON_DIR(IN);
}
