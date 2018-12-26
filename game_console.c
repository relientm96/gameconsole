/*************************************************************************
Title:    game_console Template
Initial Author:   David Jahshan
Extended by : Matthew Yong Fen Yi, 765353
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Main and functions for Game Console basic sample code

*************************************************************************/

#include "game_console.h" 
#include "function_prototypes.h"
#include "character.h"

/*---Global Variables---*/
// "Extern" tells game_console.c that the same variable has been defined in another c file
// "violatile" tells compiler to not optimize while compilling, ensuring state of variables unchanged

//Frame Buffer 
extern byte frame_buffer[MAX_PAGE][MAX_COL];
//Brightness Variable
extern byte brightness;
//Timer Variable (16 bits)
extern unsigned short time;
//Battery Health
extern unsigned short BatteryHealth;

/*---Flags---*/
//Battery Low Flag
extern volatile byte batteryLowFlag;
//Button Register
extern volatile byte buttonFlag;

//Cursor for MAIN MENU
byte cursor_page = ETCH_PAGE; //Initialized at ETCH
//Battery Health from ADC (16 bit number)
unsigned short batteryHealth = OFF;

//Main Loop
int main(void)
{

	//Perform Initializations after Power On
	init_All();
	
	//Welcome
	welcome_page();
	
	//Set your brightness
	brightness_page();

	//Master loop for MAIN MENU
	while (MAIN_MENU) {
			
		//Always turn off Button Flag in Loop when no button pressed 
		buttonFlag = OFF;
		
		//Print to LCD
		printGameMenu();
		printCursor(cursor_page);
		
		//Print Message if Battery Low
		if( (time == 0)&&(batteryLowFlag) ){
			wholeScreen(CLEAR, PAGEOFF);
			//Print Low Battery Message
			printBatteryLow();
			wholeScreen(CLEAR, PAGEOFF);
		}
		
		//When button interrupt turns button flag on
		if(buttonFlag){
		 
			//Play Etch a Sketch
			if ( (ACT1_BUTTON)&&(cursor_page==ETCH_PAGE) ){
				wholeScreen(CLEAR, PAGEOFF);
				etchASketch();
			}
			
			//Play Pong
			if ( (ACT1_BUTTON)&&(cursor_page==PONG_PAGE) ){
				wholeScreen(CLEAR, PAGEOFF);
				pongOpening();
				pong();	
			}
			
			//Guess
			if ( (ACT1_BUTTON)&&(cursor_page==GUESS_PAGE) ){
				wholeScreen(CLEAR, PAGEOFF);
				printGuessOpening();
				wholeScreen(CLEAR, PAGEOFF);
				guess();	
			}
			//Flappy Bird
			if(RIGHT_BUTTON){
				wholeScreen(CLEAR,PAGEOFF);
				flappyBirdOpening();
				wholeScreen(CLEAR,PAGEOFF);
				flappyBird();
				wholeScreen(CLEAR,PAGEOFF);
			}
			
			//Move Cursor Down
			if(DOWN_BUTTON){
				wholeScreen(CLEAR, PAGEOFF);
				cursor_page+=2;
				if(cursor_page>=6) cursor_page = 6;
			}
			//Move Cursor Up
			if(UP_BUTTON){
				wholeScreen(CLEAR, PAGEOFF);
				cursor_page-=2;
				if(cursor_page<=2) cursor_page = 2;
			}
			//Go back to Brightness Options
			if(LEFT_BUTTON){
				wholeScreen(CLEAR, PAGEOFF);
				brightness_page();
			}
			
		}
		
	}
}

//Welcome Display
void welcome_page(){
	//Welcome Message
	while(WELCOME_PAGE){
		
		//Print Message
		printWelcome();
		//Print Count Down Timer
		drawNums(1,CHAR_INT,time);
		
		//If user presses action 1, moves to brightness settings
		if(buttonFlag){
			if( (ACT1_BUTTON) ){
				wholeScreen(CLEAR, PAGEOFF);
				clearFrameBuffer();
				break;
			}
		}
		
		//If user does not press anything, screen moves to brightness settings
		//After 10 Seconds
		if(time == 0){
			wholeScreen(CLEAR, PAGEOFF);
			clearFrameBuffer();
			break;
		}
	}
}

//Initialize All Components 
void init_All(){
	
	//Delay time when booted up
	_delay_ms(10); 
	
	//Initializing Components
	initialize_backLight();
	initialize_LOWLED();
	initialize_Buttons();
	init_BattCheck();
	
	//Enable Global Interrupts
	sei();

	//Button Interrupt
	init_ButtonInterrupt();
	//Timer Interrupt
	init_TimerInterrupt();
	
	/*-SPI-*/
	//Initialize Microcontroller as Master
	init_Master();
	/*Initialize Slaves*/
	init_LCD(); 	
	
	//Clear Junk in Frame Buffer
	clearFrameBuffer();
	//Clear Screen
	wholeScreen(CLEAR, PAGEOFF);
}


