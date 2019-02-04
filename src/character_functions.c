/*-----------Character Functions------------*/

#include "game_console.h"
#include "character.h"
#include "function_prototypes.h"

//Timer Variable (16 bits)
extern unsigned short time;
//Button Register
extern volatile byte buttonFlag;

//Helper Function to reverse bits( MSB - LSB or LSB to MSB)
//Uses Bit Shifting
//Taken from Stack Overflow
byte bit_Reverse(byte c){
    c = ((c>>1)&0x55)|((c<<1)&0xAA);
    c = ((c>>2)&0x33)|((c<<2)&0xCC);
    c = (c>>4) | (c<<4); 
	return c;
}

//Draws a given character onto the LCD screen
void charLetter(byte text_page, byte text_column, byte a0, byte a1, byte a2, byte a3, byte a4, byte a5, byte a6, byte a7){
	
	/*Print Character to Screen*/
	
	//Reverse Bits 
	a0 = bit_Reverse(a0);
	a1 = bit_Reverse(a1);
	a2 = bit_Reverse(a2);
	a3 = bit_Reverse(a3);
	a4 = bit_Reverse(a4);
	a5 = bit_Reverse(a5);
	a6 = bit_Reverse(a6);
	a7 = bit_Reverse(a7);
	
	//Start at given page
	select_page(text_page - 0);
	
	//Printing Column from Right to Left
	//Column from bottom to top 
	/* a0 a1 a2 a3 a4 a5 a6 a7 */
								
	select_column(text_column - 0); 
	LCD_tx(a7, DATA );
	select_column(text_column - 1 );
	LCD_tx(a6, DATA );
	select_column(text_column - 2 );               
	LCD_tx(a5, DATA );
	select_column(text_column - 3 );
	LCD_tx(a4, DATA );
	select_column(text_column - 4 );
	LCD_tx(a3, DATA );
	select_column(text_column - 5 );
	LCD_tx(a2, DATA );
	select_column(text_column - 6 );
	LCD_tx(a1, DATA );
	select_column(text_column - 7 );
	LCD_tx(a0, DATA );
}

/*----Character Functions----*/

//Misc
void charSPACE(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}
void charCURSOR(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
}
void charBall(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x18, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x18);
}
void charPlayerOneBar(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00);
}
void charPlayerTwoBar(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF);
}
//Characters
void charA(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x7, 0x18, 0x68, 0x88, 0x88, 0x68, 0x18, 0x7);
}
void charB(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x6E);
}
void charC(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81);
}
void charD(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C);
}
void charE(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91);
}
void charF(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90);
}
void charG(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x7E, 0x81, 0x81, 0x81, 0x89, 0x89, 0x8E, 0x88);
}
void charH(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFF);
}
void charI(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x81, 0x81, 0x81, 0xFF, 0xFF, 0x81, 0x81, 0x81);
}
void charJ(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x81, 0x81, 0x81, 0x81, 0xFE, 0x80, 0x80, 0x80);
}
void charK(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x10, 0x10, 0x10, 0x18, 0x24, 0x42, 0x81);
}
void charL(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1);
}
void charM(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x80, 0x40, 0x20, 0x20, 0x40, 0x80, 0xFF);
}
void charN(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x80, 0x40, 0x30, 0xC, 0x2, 0x1, 0xFF);
}
void charO(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E);
}
void charP(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70);
}
void charQ(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFE, 0x81, 0x81, 0x81, 0x81, 0x85, 0x82, 0x7D);
}
void charR(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x90, 0x90, 0x98, 0x94, 0x92, 0x90, 0x60);
}
void charS(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x61, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x8E);
}
void charT(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0x80);
}
void charU(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFE, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0xFE);
}
void charV(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xE0, 0x18, 0x6, 0x1, 0x1, 0x6, 0x18, 0xE0);
}
void charW(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xFF, 0x1, 0x2, 0x4, 0x4, 0x2, 0x1, 0xFF);
}
void charX(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81);
}
void charY(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x80, 0x40, 0x20, 0x1F, 0x1F, 0x20, 0x40, 0x80);
}
void charZ(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x80, 0x83, 0x85, 0x89, 0x91, 0xA1, 0xC1, 0x1);
}

//Numbers
void char1(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x1, 0x31, 0x61, 0xFF, 0xFF, 0x1, 0x1, 0x1);
}
void char2(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x21, 0x43, 0x85, 0x85, 0x89, 0x89, 0x51, 0x21);
}
void char3(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x81, 0x81, 0x81, 0x81, 0x99, 0x99, 0x99, 0x66);
}
void char4(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xF8, 0x8, 0x8, 0x8, 0xFF, 0x8, 0x8, 0x8);
}
void char5(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0xF9, 0x91, 0xA1, 0xA1, 0xA1, 0xA1, 0x91, 0x8E);
}
void char6(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x3C, 0x52, 0x91, 0x91, 0x91, 0x91, 0x92, 0x8C);
}
void char7(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x80, 0x80, 0x80, 0x88, 0x88, 0xFF, 0x8, 0x8);
}
void char8(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x6E, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x6E);
}
void char9(byte text_page, byte text_column){
	charLetter(text_page,text_column, 0x30, 0x48, 0x84, 0x84, 0x84, 0x84, 0x88, 0xFF);
}

//Switch Function to draw Numbers easily
void drawNums(byte text_page, byte text_column, byte num){
	switch (num){
		case 0:
			charO(text_page,text_column);
			break;
		case 1:
			char1(text_page,text_column);
			break;
		case 2:
			char2(text_page,text_column);
			break;
		case 3:
			char3(text_page,text_column);
			break;
		case 4:
			char4(text_page,text_column);
			break;
		case 5:
			char5(text_page,text_column);
			break;
		case 6:
			char6(text_page,text_column);
			break;
		case 7:
			char7(text_page,text_column);
			break;
		case 8:
			char8(text_page,text_column);
			break;
		case 9:
			char9(text_page,text_column);
			break;	
		
		case 100:
			char1(text_page,text_column);
			char1(text_page,text_column+CHAR_INT);
			char9(text_page,text_column+CHAR_INT*2);
			break;
			
		//Default Value if number too large
		//If number of 9 print 255
		default:
			char2(text_page,text_column);
			char5(text_page,text_column+CHAR_INT);
			char5(text_page,text_column+CHAR_INT*2);
			break;
	}
}

/*------------Printing Menu Displays and Misc------------------*/

//Welcome Page
void printWelcome(){
	// Message: WELCOME
	charW(1,INIT_COL-CHAR_INT*3);
	charE(1,INIT_COL-CHAR_INT*2);
	charL(1,INIT_COL-CHAR_INT);
	charC(1,INIT_COL);
	charO(1,INIT_COL+CHAR_INT);
	charM(1,INIT_COL+CHAR_INT*2);
	charE(1,INIT_COL+CHAR_INT*3);
	
	// Message: Master
	charM(3,INIT_COL-CHAR_INT*3);
	charA(3,INIT_COL-CHAR_INT*2);
	charS(3,INIT_COL-CHAR_INT);
	charT(3,INIT_COL);
	charE(3,INIT_COL+CHAR_INT);
	charR(3,INIT_COL+CHAR_INT*2);
	
	//Message Press ACT1 
	charP(5,INIT_COL-CHAR_INT*4);
	charR(5,INIT_COL-CHAR_INT*3);
	charE(5,INIT_COL-CHAR_INT*2);
	charS(5,INIT_COL-CHAR_INT*1);
	charS(5,INIT_COL);
	charSPACE(5,INIT_COL+CHAR_INT);
	charA(5,INIT_COL+CHAR_INT*2);
	charC(5,INIT_COL+CHAR_INT*3);
	charT(5,INIT_COL+CHAR_INT*4);
	char1(5,INIT_COL+CHAR_INT*5);
	
}

//Printing Brightness Menu
void printBrightnessInstructions(){
	
	//UP BRIGHT
	charU(1,INIT_COL-CHAR_INT*4);
	charP(1,INIT_COL-CHAR_INT*3);
	charSPACE(1,INIT_COL-CHAR_INT*2);
	charB(1,INIT_COL-CHAR_INT);
	charR(1,INIT_COL);
	charI(1,INIT_COL+CHAR_INT);
	charG(1,INIT_COL+CHAR_INT*2);
	charH(1,INIT_COL+CHAR_INT*3);
	charT(1,INIT_COL+CHAR_INT*4);
	
	//DOWN DIM
	charD(3,INIT_COL-CHAR_INT*4);
	charO(3,INIT_COL-CHAR_INT*3);
	charW(3,INIT_COL-CHAR_INT*2);
	charN(3,INIT_COL-CHAR_INT);
	charSPACE(3,INIT_COL);
	charD(3,INIT_COL+CHAR_INT);
	charI(3,INIT_COL+CHAR_INT*2);
	charM(3,INIT_COL+CHAR_INT*3);
	
	//RIGHT 2 GO
	charR(5,INIT_COL-CHAR_INT*4);
	charI(5,INIT_COL-CHAR_INT*3);
	charG(5,INIT_COL-CHAR_INT*2);
	charH(5,INIT_COL-CHAR_INT*1);
	charT(5,INIT_COL);
	charSPACE(1,INIT_COL+CHAR_INT);
	char2(5,INIT_COL+CHAR_INT*2);
	charSPACE(1,INIT_COL+CHAR_INT*3);
	charG(5,INIT_COL+CHAR_INT*4);
	charO(5,INIT_COL+CHAR_INT*5);

}

//Game Menu Message
void printGameMenu(){
	
	//GAME MENU
	charG(0,CHAR_INT);
	charA(0,CHAR_INT*2);
	charM(0,CHAR_INT*3);
	charE(0,CHAR_INT*4);
	charSPACE(0,CHAR_INT*5);
	charM(0,CHAR_INT*6);
	charE(0,CHAR_INT*7);
	charN(0,CHAR_INT*8);
	charU(0,CHAR_INT*9);
	
	//ETCH 
	charE(ETCH_PAGE,CHAR_INT);
	charT(ETCH_PAGE,CHAR_INT*2);
	charC(ETCH_PAGE,CHAR_INT*3);
	charH(ETCH_PAGE,CHAR_INT*4);
	
	//PONG
	charP(PONG_PAGE,CHAR_INT);
	charO(PONG_PAGE,CHAR_INT*2);
	charN(PONG_PAGE,CHAR_INT*3);
	charG(PONG_PAGE,CHAR_INT*4);
	
	//GUESS
	charG(GUESS_PAGE,CHAR_INT);
	charU(GUESS_PAGE,CHAR_INT*2);
	charE(GUESS_PAGE,CHAR_INT*3);
	charS(GUESS_PAGE,CHAR_INT*4);
	charS(GUESS_PAGE,CHAR_INT*5);
	
}

//Print Cursor for Game Menu
void printCursor(byte cursor_page){
	_delay_ms(40);
	charCURSOR(cursor_page,CHAR_INT*8);
}

/*--------Etch a Sketch stuff------*/

//Etch A Sketch Opening
void printEtchOpening(){
	_delay_ms(750);
	//ETCH
	charE(1,CHAR_INT*2);
	charT(1,CHAR_INT*3);
	charC(1,CHAR_INT*4);
	charH(1,CHAR_INT*5);
	//A
	charA(3,CHAR_INT*2);
	//SKETCH
	charS(5,CHAR_INT*2);
	charK(5,CHAR_INT*3);
	charE(5,CHAR_INT*4);
	charT(5,CHAR_INT*5);
	charC(5,CHAR_INT*6);
	charH(5,CHAR_INT*7);
	_delay_ms(2000);
}

/*--------Pong Stuff----------------*/

//Opening Screen
void pongOpening(){
	_delay_ms(750);
	//PONG
	charP(3,CHAR_INT*4);
	charO(3,CHAR_INT*5);
	charN(3,CHAR_INT*6);
	charG(3,CHAR_INT*7);
	_delay_ms(2000);
}

//Player One Win Message
void playerOneWins(){
	//P1 WINS
	charP(3,CHAR_INT*3);
	char1(3,CHAR_INT*4);
	charSPACE(3,CHAR_INT*5);
	charW(3,CHAR_INT*6);
	charI(3,CHAR_INT*7);
	charN(3,CHAR_INT*8);
	charS(3,CHAR_INT*9);
	_delay_ms(3000);
}

//Player Two Win Message
void playerTwoWins(){
	//P2 WINS
	charP(3,CHAR_INT*3);
	char2(3,CHAR_INT*4);
	charSPACE(3,CHAR_INT*5);
	charW(3,CHAR_INT*6);
	charI(3,CHAR_INT*7);
	charN(3,CHAR_INT*8);
	charS(3,CHAR_INT*9);
	_delay_ms(3000);	
}

//Player One Player Bar
void printPlayerOneBar(byte text_page){
	charPlayerOneBar(text_page,CHAR_INT);
}

//Player Two Player Bar
void printPlayerTwoBar(byte text_page){
	charPlayerTwoBar(text_page,AI_COLUMN);
}

//AI Select screen
byte printAIselect(){
	
	//Initialize Cursor Positions
	byte cursor_col = INIT_COL-CHAR_INT;
	byte cursor_old = 0;
	
	//SELECT
	charS(1,CHAR_INT*3);
	charE(1,CHAR_INT*4);
	charL(1,CHAR_INT*5);
	charE(1,CHAR_INT*6);
	charC(1,CHAR_INT*7);
	charT(1,CHAR_INT*8);
	
	//AI
	charA(3,CHAR_INT*5);
	charI(3,CHAR_INT*6);
	
	//1 2
	char1(5,INIT_COL-CHAR_INT);
	char2(5,INIT_COL+CHAR_INT);
	
	//Keep Looping until choice is made
	while(TRUE){
		
		buttonFlag = OFF;
		
		//Delay to print onto screen
		_delay_ms(100);
		
		//Print Cursor locations
		charCURSOR(7,cursor_col);
		//Store current (old) position of cursor to be cleared later
		cursor_old = cursor_col; 
		
		/*Button Actions*/
		
		//Move Cursor to Right
		
		if(buttonFlag){
			if(RIGHT_BUTTON){
				cursor_col = cursor_col + CHAR_INT*2;
				if(cursor_col > INIT_COL+CHAR_INT) cursor_col = INIT_COL+CHAR_INT;
				charSPACE(7,cursor_old);
			}
			
			//Move Cursor to Left
			if(LEFT_BUTTON){
				cursor_col = cursor_col - CHAR_INT*2;
				if(cursor_col < INIT_COL-CHAR_INT) cursor_col = INIT_COL-CHAR_INT;
				charSPACE(7,cursor_old);
			}
			
			//Make Selection
			if(ACT1_BUTTON){
				if(cursor_col == INIT_COL-CHAR_INT) return 1;
				if(cursor_col == INIT_COL+CHAR_INT) return 2;
			}
		}
		
	}
}

//Pause Message in between points
void printPauseMessage(byte p1, byte p2){

	//2 Second Timer
	time = 2;
	
	while(time > 0){
		//READY
		charR(3,INIT_COL-CHAR_INT*2);
		charE(3,INIT_COL-CHAR_INT);
		charA(3,INIT_COL);
		charD(3,INIT_COL+CHAR_INT);
		charY(3,INIT_COL+CHAR_INT*2);
		//TIME 
		drawNums(5,INIT_COL,time);
	}
	
}

/*-----------Guess Game-----------------*/ 

//Print Opening Message
void printGuessOpening(){
	_delay_ms(750);
	//Guess
	charG(3,INIT_COL-CHAR_INT*2);
	charU(3,INIT_COL-CHAR_INT);
	charE(3,INIT_COL);
	charS(3,INIT_COL+CHAR_INT);
	charS(3,INIT_COL+CHAR_INT*2);
	_delay_ms(2000);
}

//Print Choices Onto Screen
void printChoices(){
	//1 2 3
	char1(2,INIT_COL - CHAR_INT*2);
	char2(2,INIT_COL);
	char3(2,INIT_COL + CHAR_INT*2);
}	

//Cursor to select which option
void guessCursor(byte column){
	_delay_ms(60);
	charCURSOR(4,column);
}

//Print Good Job message when Correct Choice Chosen
void printRightAnswer(byte score){
	//GOOD
	charG(1,CHAR_INT);
	charO(1,CHAR_INT*2);
	charO(1,CHAR_INT*3);
	charD(1,CHAR_INT*4);
	//JOB
	charJ(3,CHAR_INT);
	charO(3,CHAR_INT*2);
	charB(3,CHAR_INT*3);
	//SCORE 
	charS(5,CHAR_INT);
	charC(5,CHAR_INT*2);
	charO(5,CHAR_INT*3);
	charR(5,CHAR_INT*4);
	charE(5,CHAR_INT*5);
	charSPACE(5,CHAR_INT*6);
	drawNums(5,CHAR_INT*7,score);
	_delay_ms(1200);
	wholeScreen(CLEAR, PAGEOFF);
}

//Print Wrong Message when wrong choice selected 
void printWrongAnswer(byte answer){
	//WRONG
	charW(2,INIT_COL-CHAR_INT*2);
	charR(2,INIT_COL-CHAR_INT);
	charO(2,INIT_COL);
	charN(2,INIT_COL+CHAR_INT);
	charG(2,INIT_COL+CHAR_INT*2);
	
	//ANS--Number
	charA(4,INIT_COL-CHAR_INT*2);
	charN(4,INIT_COL-CHAR_INT);
	charS(4,INIT_COL);
	charSPACE(4,INIT_COL+CHAR_INT);
	drawNums(4,INIT_COL+CHAR_INT*2,answer);
	_delay_ms(1200);
	wholeScreen(CLEAR, PAGEOFF);
	GameOver();
}

//Game Over Message
void GameOver(){
	//Game
	charG(2, CHAR_INT*4);
	charA(2, CHAR_INT*5);
	charM(2, CHAR_INT*6);
	charE(2, CHAR_INT*7);
	//Over
	charO(4, CHAR_INT*4);
	charV(4, CHAR_INT*5);
	charE(4, CHAR_INT*6);
	charR(4, CHAR_INT*7);
	_delay_ms(2000);
	wholeScreen(CLEAR,PAGEOFF);
}

//Winning Message for Guess Game
void printWinGuess(){
	wholeScreen(CLEAR, PAGEOFF);
	//YOU
	charY(3,INIT_COL-CHAR_INT*3);
	charO(3,INIT_COL-CHAR_INT*2);
	charU(3,INIT_COL-CHAR_INT);
	charSPACE(3,INIT_COL);
	//WIN
	charW(3,INIT_COL+CHAR_INT);
	charI(3,INIT_COL+CHAR_INT*2);
	charN(3,INIT_COL+CHAR_INT*3);
	_delay_ms(2000);
	wholeScreen(CLEAR, PAGEOFF);
}

//Print Monty Hall
void printMontyHall(byte option){
	wholeScreen(CLEAR,PAGEOFF);
	//MONTY
	charM(6, CHAR_INT);
	charO(6, CHAR_INT*2);
	charN(6, CHAR_INT*3);
	charT(6, CHAR_INT*4);
	charY(6, CHAR_INT*5);
	//HALL
	charH(6, CHAR_INT*7);
	charA(6, CHAR_INT*8);
	charL(6, CHAR_INT*9);
	charL(6, CHAR_INT*10);
	
	//Print Respective Choices 
	
	//If Two Selected
	if(option == INIT_COL){
		char1(2,INIT_COL - CHAR_INT*2);
		char3(2,INIT_COL + CHAR_INT*2);
	}
	//If One Selected
	else if(option == INIT_COL - CHAR_INT*2){
		char2(2,INIT_COL);
		char3(2,INIT_COL + CHAR_INT*2);
	}
	//If Three Selected
	else {
		char1(2,INIT_COL - CHAR_INT*2);
		char2(2,INIT_COL);	
	}
}

//For Battery Low Message
void printBatteryLow(){
	
	//BATTERY
	charB(2,CHAR_INT*3);
	charA(2,CHAR_INT*4);
	charT(2,CHAR_INT*5);
	charT(2,CHAR_INT*6);
	charE(2,CHAR_INT*7);
	charR(2,CHAR_INT*8);
	charY(2,CHAR_INT*9);
	
	//LOW
	charL(4,CHAR_INT*5);
	charO(4,CHAR_INT*6);
	charW(4,CHAR_INT*7);

	_delay_ms(1500);
}

/*--------Flappy Bird----------*/

//Print Opening
void flappyBirdOpening(){
	charF(2,CHAR_INT*3);
	charL(2,CHAR_INT*4);
	charA(2,CHAR_INT*5);
	charP(2,CHAR_INT*6);
	charP(2,CHAR_INT*7);
	charY(2,CHAR_INT*8);
	
	charB(4,CHAR_INT*4);
	charI(4,CHAR_INT*5);
	charR(4,CHAR_INT*6);
	charD(4,CHAR_INT*7);
	
	_delay_ms(1500);
}	

//Count Down Before game starts
void countDown(){
	time = 3;
	while(time>0){
		drawNums(3,INIT_COL,time);	
	}
	charSPACE(3,INIT_COL);
}

//Print the obstacles coming in
void printObstacles(byte height, byte column){
	
	//Print Obstacles from bottom (7) to given height 
	byte drawHeight = 7;
	
	while(drawHeight >= height){
		charCURSOR(drawHeight,column);
		drawHeight--;
	}
	
}

//Clear Obstacles as they pass by
void charCLEAROBSTACLE(byte obstacle_col_old){
	
	//Start at this height
	byte height = 1;
	
	//Print Spaces from ground up 
	while(height <= 7){
		charSPACE(height,obstacle_col_old);
		height++;
	}
	
}

//Print BANG Message when bird collides with obstacle
void printColiisonMessage(){
	//BANG
	charB(3,INIT_COL-CHAR_INT*1);
	charA(3,INIT_COL);
	charN(3,INIT_COL + CHAR_INT);
	charG(3,INIT_COL + CHAR_INT*2);
	_delay_ms(1500);
}

//If you press too much up, you die
void printTooHigh(){
	
	//Too
	charT(2,INIT_COL-CHAR_INT);
	charO(2,INIT_COL);
	charO(2,INIT_COL+CHAR_INT);
	
	//High
	charH(4, INIT_COL - CHAR_INT);
	charI(4, INIT_COL);
	charG(4, INIT_COL + CHAR_INT);
	charH(4, INIT_COL + CHAR_INT*2);
	
	_delay_ms(1500);
}


