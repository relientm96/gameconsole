/*----Guessing Game----*/

#include "game_console.h"
#include "function_prototypes.h"
#include "character.h"

//Button Register
extern volatile byte buttonFlag;  
//Timer Variable (16 bits)
extern unsigned short time;

//Guess
void guess(){
	
	//Initialize Parameters
	byte cursor_pos = INIT_COL - CHAR_INT*2; //Initial Cursor Position
	byte pos_old = 0; //Old Cursor Position
	byte generate; //Store Random generated number
	byte choice = INIT_COL - CHAR_INT*2 ; //Choice (initialized to cursor_pos
	byte score = 0; //Current player score
	byte selected = 0; //Used to store player's selected option
	
	//Store Unselected Options
	byte otherOption1 = 0;
	byte otherOption2 = 0;
	byte numb = 0;
	
	//Seed to generate Random number (Tick value from counter used)
	srand(TCNT1);
	
	while(GAME_LOOP){
		
		//Print the choice to the screen
		printChoices();
		
		//Set Button Flag to Zero (prevent holding down)
		buttonFlag = OFF;
		
		//Generate Answers and Other Available Answers
		generate = rand()%3; //Randomly choose a number from 1 -> 3
	
		//Generate Answer positions
		if(generate == 0){
			choice = INIT_COL - CHAR_INT*2; //Answer: 1
			otherOption1 = INIT_COL; //Other option: 2
			otherOption2 = INIT_COL + CHAR_INT*2; //Other option: 3
		}
		
		if(generate == 1){
			choice = INIT_COL; //Answer: 2
			otherOption1 = INIT_COL - CHAR_INT*2; //Other Option: 1 
			otherOption2 = INIT_COL + CHAR_INT*2;// Other option: 3
		}
		
		if(generate == 2){
			choice = INIT_COL + CHAR_INT*2; //Answer: 3
			otherOption1 = INIT_COL - CHAR_INT*2;// Other Option: 1
			otherOption2 = INIT_COL;// Other Option: 2
		}
			
		//Boundaries for Cursor
		if(cursor_pos>(INIT_COL+CHAR_INT*2)) cursor_pos = INIT_COL+CHAR_INT*2;
		if(cursor_pos<(INIT_COL-CHAR_INT*2)) cursor_pos = INIT_COL-CHAR_INT*2;
		//Print Cursor Position
		guessCursor(cursor_pos);
		
		//Game Win Senario
		if(score==FINAL_SCORE){
			printWinGuess();
			break;
		}
		
		//Button Actions
		if(buttonFlag){
			//Return to Game Menu
			if(ACT2_BUTTON){
				clearFrameBuffer();
				wholeScreen(CLEAR, PAGEOFF);
				break;	
			}	
			//Move Cursor to Left
			if(LEFT_BUTTON){
				pos_old = cursor_pos;
				cursor_pos = cursor_pos - CHAR_INT*2;
				charSPACE(4,pos_old);
			}
			//Move Curosr to Right
			if(RIGHT_BUTTON){
				pos_old = cursor_pos;
				cursor_pos = cursor_pos + CHAR_INT*2;
				charSPACE(4,pos_old);
			}
			//Check if Correct Answer After Selection
			if(ACT1_BUTTON){		
				
					//Wrongly Selected Position
					selected = cursor_pos;
					
					//Choose Random Number Between Other option 1 or option2
					numb = rand()%2;
					
					//Print Monty Hall Message
					//From Randomly selected number ( 1 or 2 )
					if(numb == 0) printMontyHall(otherOption1);
					else printMontyHall(otherOption2);
						
					//Set Up timer (5 seconds)
					time = 5;
					
					//Monty Hall Mode
					while(GAME_LOOP){
							
						//Turn Off Button Flag if no button pressed
						buttonFlag = OFF;
						//Print Cursor Position
						guessCursor(cursor_pos);
						//Print Timer
						drawNums(1,CHAR_INT,time);
						
						//Game Over if Player Runs out of Time
						if(time == 0){
							wholeScreen(CLEAR,PAGEOFF);
							GameOver();
							return;		
						}
						
						//When Button Pressed
						if(buttonFlag){
							//If a Choice is selected
							if(ACT1_BUTTON){
								//Add 1 to score if right choice selected
								if(cursor_pos == choice){
									score++;
									wholeScreen(CLEAR,PAGEOFF);
									printRightAnswer(score);
									break;	
								}
								//Wrong selection, Exit Game
								else{
									wholeScreen(CLEAR,PAGEOFF);
									printWrongAnswer(generate+1);
									return;			
								}
							}
							//Move cursor to left
							if(LEFT_BUTTON){
								pos_old = cursor_pos;
								cursor_pos = cursor_pos - CHAR_INT*2;
								charSPACE(4,pos_old);	
							}
							//Move Cursor to Right
							if(RIGHT_BUTTON){
								pos_old = cursor_pos;
								cursor_pos = cursor_pos + CHAR_INT*2;
								charSPACE(4,pos_old);
							}
						}
					}
			}
		}
	}
}