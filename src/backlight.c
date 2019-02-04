/*-----Backlight-----*/

#include "game_console.h"
#include "function_prototypes.h"

//Initialized to Init brightness
byte brightness = INIT_BRIGHTNESS; 
//Button Register
extern volatile byte buttonFlag;

void initialize_backLight(){

	//Turning Off pins near LCD control (as I soldered them over)
	P_D_4(OFF);
	P_D_5(OFF);
	P_D_6(OFF);
	
	 //Enabling TimerCounter2 Function on PWM pin
	LCD_CTRL_DIR(OUT);

	/*--PWM Specifications--*/
	//---Fast PWM Mode: WGM21,WGM20 = (1,1),
	//---Compare Output Mode: Clear on match,Set OC2 at BOTTOM,
	//	(non inverting mode): COM21,COM20 = (1,0)
	//---Clock Select: clk/64 : CS22,CS21,CS20 = (1,0,0)  
	TCCR2 = _BV(WGM21)|_BV(WGM20)|_BV(COM21)|_BV(CS22);

	//Initialize brightness value with initial brightness
	OCR2 = brightness;
}

//Brightness Display
void brightness_page(){
	//Brightness Options
	while(BRIGHTNESS_PAGE){
		buttonFlag = 0;
		printBrightnessInstructions();
		//Control BackLight Levels (0,50,100,150,200)
		if(buttonFlag){
			if (UP_BUTTON && brightness<=(MAX_BRIGHTNESS-BRIGHT_INTERVAL)){ 
				brightness += BRIGHT_INTERVAL;
				OCR2 = brightness; //Set New Brightness
				_delay_ms(150);
			}
			if (DOWN_BUTTON && brightness>=(MIN_BRIGHTNESS+BRIGHT_INTERVAL)){ 
				brightness -= BRIGHT_INTERVAL;
				OCR2 = brightness;  //Set New Brightness
				_delay_ms(150);
			}
			if(RIGHT_BUTTON){
				clearFrameBuffer();
				wholeScreen(CLEAR, PAGEOFF);
				break;	
			}
		}
	}
}
