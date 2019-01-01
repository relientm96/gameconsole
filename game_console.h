/*************************************************************************
Title:    Game Console Template Header File
Inital Author:   David Jahshan
Extended by : (PUT YOUR NAME HERE) (PUT YOUR STUDENT NUMBER HERE) 
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Macros for Game Console

*************************************************************************/

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>

#define byte unsigned char 

/*---ON OFF---*/
#define ON 0xFF
#define OFF 0x00
#define HIGH 0xFF
#define LOW 0x00
#define IN 0x00
#define OUT 0xFF
#define ALL 0xFF
#define TRUE 1
#define FALSE 0
#define FORWARD 0x00
#define BACK 0xFF
#define CMD 0x00
#define DATA 0xFF

/*--Infinite Loops for Different Screens--*/
#define WELCOME_PAGE 		1
#define BRIGHTNESS_PAGE 	1
#define MAIN_MENU 			1
#define GAME_LOOP 			1

//Main Menu Row Positions
#define ETCH_PAGE  			2
#define PONG_PAGE  			4
#define GUESS_PAGE 			6

//Backlight Levels 
#define INIT_BRIGHTNESS		100 //Initial Brightness after PowerOn
#define MAX_BRIGHTNESS		200 //Maximum Level 
#define MIN_BRIGHTNESS		0 //Minimum Level
#define BRIGHT_INTERVAL		50 //Increments between Levels

//Battery Level
#define VBATT_LEVEL 		440 // (1.1*1024)/2.56 = 440

//Timer Stuff
#define TICKS_INIT			57723  //Counts from this number to 65535 to cause overflow every second
#define TARGET             	0      //Timer Decrements down to 0
#define TIMER_INIT          9	   //Timer Resets to 9 after 10 seconds
 
/*---Constants---*/

//For wholeScreen function
#define CLEAR			0

//LCD Constants
#define CMD_PAGE		0xB0 // command page address
#define CMD_COL_LSB 	0x00
#define CMD_COL_MSB 	0x10 //0001 0000 in binary
#define PAGEOFF			0x00
#define PAGEON			0xFF
#define MAX_ROW			64
#define MAX_PAGE		8
#define MAX_COL			102
#define PIXELPERPAGE	8

//Etch A Sketch
//Starting point of etcha sketch cursor, middle of screen
#define INIT_ROW		32
#define INIT_COL		53

//Pong
#define AI_COLUMN       101
#define WIN_SCORE       9
#define STARTINGPAGE	3
#define P1SCORELOCATION 9
#define P2SCORELOCATION 99

//Guess Game
#define FINAL_SCORE 	6

//Character Drawing Constants
#define CHAR_INT 		9  //Interval between each column for character display

/*SET and GET MACRO*/
//Set Value at Port and Mask Bit Number
#define SET(PORT,MASK,VALUE) PORT = ((MASK & VALUE) | (PORT & ~MASK))
//Get Value at Port and Mask Bit Number
#define GET(PORT,MASK) PORT & MASK

/*------------Device Direction Macros----------------*/
// Decides if pin is an Input or Output 
//If needed: #define MULTI_LINES_DIR(DIR) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

//Devices Direction MACROs 
/*--writing 1 to DDRx makes it an output pin
  --writing 0 to DDRx makes it an input pin */

// INTERRUPT
#define BTN_INTERRUPT_DIR(DIR) 	SET(DDRD,_BV(PD2),DIR)

//Led
#define BAT_LOW_LED_DIR(DIR) 	SET(DDRB,_BV(PB2),DIR)

//Battery
#define VBATT_DIR(DIR)			SET(DDRA,_BV(PA2),DIR)

//LCD
#define LCD_CTRL_DIR(DIR) 		SET(DDRD,_BV(PD7),DIR)
#define LCD_CD_DIR(DIR)			SET(DDRA,_BV(PA1),DIR)
#define LCD_RST_DIR(DIR)		SET(DDRA,_BV(PA3),DIR)
#define LCD_CS_DIR(DIR)			SET(DDRD,_BV(PD6),DIR)

//Buttons
#define UP_BUTTON_DIR(DIR) 		SET(DDRA,_BV(PA4),DIR)
#define DOWN_BUTTON_DIR(DIR) 	SET(DDRC,_BV(PC7),DIR)
#define LEFT_BUTTON_DIR(DIR) 	SET(DDRC,_BV(PC6),DIR)
#define RIGHT_BUTTON_DIR(DIR) 	SET(DDRA,_BV(PA5),DIR)
#define ACT1_BUTTON_DIR(DIR) 	SET(DDRB,_BV(PB0),DIR)
#define ACT2_BUTTON_DIR(DIR)	SET(DDRA,_BV(PA6),DIR)

//SPI Pins for MicroController
#define SS_DIR(DIR)				SET(DDRD,_BV(PD6),DIR)
#define MISO_DIR(DIR) 			SET(DDRB,_BV(PB6),DIR)
#define SCK_DIR(DIR) 			SET(DDRB,_BV(PB7),DIR)
#define MOSI_DIR(DIR) 			SET(DDRB,_BV(PB5),DIR)

/*----------------------------------------------------*/
//If needed: #define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

/* PORTx: sets internal pullups */

//Devices Outputs from MicroController
#define BAT_LOW_LED(STATE) 		SET(PORTB,_BV(PB2),~STATE)
#define LCD_CTRL(STATE) 		SET(PORTD,_BV(PD7),STATE) //Used if dont want PWM
#define LCD_CD(STATE)			SET(PORTA,_BV(PA1),STATE)
#define LCD_RST(STATE) 			SET(PORTA,_BV(PA3),STATE)
#define LCD_CS(STATE) 			SET(PORTD,_BV(PD3),STATE)

//SS Pin for SPI (used in making it always HIGH)
#define SS(STATE)				SET(PORTB,_BV(PB4),STATE)

//Unsed Pins to be driven low
#define P_D_4(STATE) 			SET(PORTD,_BV(PB4),STATE)
#define P_D_5(STATE)			SET(PORTD,_BV(PB5),STATE)
#define P_D_6(STATE)			SET(PORTD,_BV(PB6),STATE)

//Devices Inputs to MicroController
/* PINx : Provides information about that pin (returns high or low depending on its state)*/
//Buttons
#define UP_BUTTON 		~GET(PINA,_BV(PA4))
#define DOWN_BUTTON 	~GET(PINC,_BV(PC7))
#define LEFT_BUTTON 	~GET(PINC,_BV(PC6))
#define RIGHT_BUTTON 	~GET(PINA,_BV(PA5))
#define ACT1_BUTTON 	~GET(PINB,_BV(PB0))
#define ACT2_BUTTON 	~GET(PINA,_BV(PA6))
//Misc
#define BTN_INTERRUPT	GET(PIND,_BV(PD2))
#define VBATT			GET(PINA,_BV(PA2))

/*-------------Internal Pull Up Macros------------------*/
#define UP_BUTTON_SET(STATE) 	SET(PORTA,_BV(PA4),STATE)
#define DOWN_BUTTON_SET(STATE) 	SET(PORTC,_BV(PC7),STATE)
#define LEFT_BUTTON_SET(STATE) 	SET(PORTC,_BV(PC6),STATE)
#define RIGHT_BUTTON_SET(STATE)	SET(PORTA,_BV(PA5),STATE)
#define ACT1_BUTTON_SET(STATE) 	SET(PORTB,_BV(PB0),STATE)
#define ACT2_BUTTON_SET(STATE) 	SET(PORTA,_BV(PA6),STATE)
