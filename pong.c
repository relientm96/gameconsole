/*---Pong---*/

#include "game_console.h"
#include "function_prototypes.h"
#include "character.h"

//Button Register
extern volatile byte buttonFlag;  

void pong(){
	
	//Clear Previous Activity
	wholeScreen(CLEAR, PAGEOFF);
	
	//Initialize Ball Parameters
	byte x = INIT_COL;
	byte x_old = 0;
	byte y = STARTINGPAGE; //(Starting Page = 3)
	byte y_old = 0;
	byte xspeed = -CHAR_INT;
	byte yspeed = -1;
	
	//Initialize Player Parameters
	
	//Player 1
	byte player1page = STARTINGPAGE;
	byte player1page_old = 0;
	byte player1score = 0;
	
	//Player 2 (AI)
	byte player2page = STARTINGPAGE;
	byte player2page_old = 0;
	byte aispeed = 1;
	byte player2score = 0;
	
	//Select AI Level
	wholeScreen(CLEAR,PAGEOFF);
	byte AI_LEVEL = printAIselect();
	wholeScreen(CLEAR,PAGEOFF);
	
	//Generate Random Number Seed (from Counter)
	srand(TCNT1);
	
	wholeScreen(CLEAR,PAGEOFF);
	//Get Ready Message
	printPauseMessage(player1score,player2score);
	//Clear Screen for Game
	wholeScreen(CLEAR,PAGEOFF);
	
	while(GAME_LOOP){
		
		//Button Actions (player 1)
		/*y position bounded between 2 and 6*/
		if(buttonFlag){	
			if(UP_BUTTON){
				if(player1page<=2) player1page = 2; //Boundary Checking
				player1page_old = player1page; //Store old player's location
				player1page-=1; //Move Bar Upwards
				charSPACE(player1page_old,CHAR_INT); //Clear old Position
			}
			if(DOWN_BUTTON){		
				if(player1page>=6) player1page = 6; //Boundary Checking
				player1page_old = player1page; //Store old player's Location
				player1page+=1; //Move Bar Downwards,
				charSPACE(player1page_old,CHAR_INT); //Clear Old Position
			}
			//Return to main menu
			if(ACT2_BUTTON){
				wholeScreen(CLEAR, PAGEOFF);
				break;	
			}	
		}
		
		//Always print Player1 New Bar Position
		printPlayerOneBar(player1page);
		
		/*---------------AI for Player 2-----------------*/
		
		//---Level 1---//
		/*AI designed to bounce up and down repeatedly*/
		if(AI_LEVEL == 1){
			//Boundaries for AI's positions
			//y bounded between 2 and 6
			//(if it reaches boundary, change it's speed)
			if( player2page >= 6){
				charSPACE(6,AI_COLUMN);
				player2page = 6;
				aispeed = -1; 
			}
			if( player2page <= 2 ){
				charSPACE(2,AI_COLUMN);
				player2page = 2;
				aispeed = 1;
			}
			
			//Update AI movement
			player2page_old = player2page; //Note Old AI's Position
			player2page = player2page + aispeed; //Update AI position
			charSPACE(player2page_old,AI_COLUMN); //Clear AI's Old Position
			
			/*
			if( xspeed == -CHAR_INT) {
				aispeed = 0;	
			}*/
			
			//Print AI's Bar
			printPlayerTwoBar(player2page);
			
		}
		
		//---Level 2---//
		/*Harder AI*/
		/*Designed to know where ball is (ball's y position) 
		  -- has error term (rand()%2) of 1) 
		  -- This means AI would have a 50% chance of missing ball */ 
		if(AI_LEVEL == 2){
			player2page_old = player2page; //Store Old Location to be cleared later
			player2page = y + rand()%2; //Update Player's Position (with error)
			charSPACE(player2page_old,AI_COLUMN); //Clear Old Position
			//Print AI's Bar
			printPlayerTwoBar(player2page);
		}
		
		/*--------------Ball Mechanics---------------*/		
		
		//X Positions
		
		//Ball Behaviour when it touches player1's bar
		if( ( y == player1page ) && (x <= CHAR_INT) ){
			xspeed = CHAR_INT; //Change Direction of ball to right
			//Update Ball Positions
			x_old = x; 
			y_old = y;
			x = x + xspeed;
			y = y + yspeed;
			charSPACE(y_old,x_old); //clear old position of ball
			charBall(y,x); //Print out ball new position
		}
		
		//Ball Behaviour when it touches player 2's bar
		if(  ( y == player2page ) && ( x >= MAX_COL-CHAR_INT) ){
			xspeed = -CHAR_INT;	//Changee Direction of ball to left
			//Update Ball Positions
			x_old = x;
			y_old = y;
			x = x + xspeed;
			y = y + yspeed;
			charSPACE(y_old,x_old); //clear old position of ball
			charBall(y,x); //Print out ball new position
		}
		
		//Y Positions
		//If it touches the ceiling
		//Change direction to downwards
		if(y<=1){
			yspeed = 1;
		}
		//If it touches the ground
		//Change direction to upwards
		if(y>=7){
			yspeed = -1;
		}
		
		//Winning Conditions and Reset of Ball
		
		//If Ball goes through player 2
		if(x>MAX_COL){
			
			//Update Score of Player 1
			player1score+=1;
			//Clear Ball's Position
			charSPACE(y,x);
			//Pause message in between points
			printPauseMessage(player1score,player2score);
			//Start Game again by clearing message
			wholeScreen(CLEAR,PAGEOFF);
			
			//Reset Ball Position to Center
			x = INIT_COL;
			y = STARTINGPAGE;
			//Ball has 50% chance to start going right/left
			xspeed = ((rand()%2) == 1)? -CHAR_INT:CHAR_INT;
		}
		
		//If Ball goes through player 1
		if(x<=8){	
			
			//Update Score of Player 2
			player2score+=1;
			//Clear Ball Location
			charSPACE(y,x);
			//Pause message in between points
			printPauseMessage(player1score,player2score);
			//Start Game again by clearing message
			wholeScreen(CLEAR,PAGEOFF);
			
			//Reset Ball Position to Center
			x = INIT_COL;
			y = STARTINGPAGE;
			//Ball has 50% chance to start going right/left
			xspeed = ((rand()%2) == 1)? -CHAR_INT:CHAR_INT;
		}
		
		//Update Ball Positions(for cases where it hasnt been updated previously)
		x_old = x;
		y_old = y;
		x = x + xspeed;
		y = y + yspeed;
		
		//Draw Ball Onto Screen (also if not updated in previous conditions)
		charBall(y,x);
		charSPACE(y_old,x_old);
		
		//Score Updates for Players
		
		//Player 1
		if(player1score >= WIN_SCORE){
			wholeScreen(CLEAR, PAGEOFF);
			playerOneWins();
			wholeScreen(CLEAR, PAGEOFF);
			break;
		}
		//Player 2
		if(player2score >= WIN_SCORE){
			wholeScreen(CLEAR, PAGEOFF);
			playerTwoWins();
			wholeScreen(CLEAR, PAGEOFF);
			break;
		}
		
		//Print Pong Scores
		drawNums(0,P1SCORELOCATION,player1score);
		drawNums(0,P2SCORELOCATION,player2score);
		
		//Delay To allow player 1 to react
		_delay_ms(250);

	}
}

