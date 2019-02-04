/*--------Flappy Bird----------*/

#include "game_console.h"
#include "function_prototypes.h"
#include "character.h"

//Timer Variable (16 bits)
extern unsigned short time;
//Button Register
extern volatile byte buttonFlag;

void flappyBird(){
	
	//Bird Parameters
	byte bird_x = 3;
	byte bird_y = CHAR_INT*3;
	byte bird_x_old = 0;
	
	//Obstacle Paramters
	byte obstacle_col = INIT_COL+CHAR_INT*4;
	byte obstacle_height = 4;
	byte obstacle_col_old = 0;
	
	//Timer Set to 1 sec, (for bird drop movement)
	time = 1;
	
	//Seed from counter
	srand(TCNT1);
	
	//Print CountDown Screen before Starting 
	countDown();
		
	while(GAME_LOOP){
		
		//Button Actions
		if(buttonFlag){
			if(UP_BUTTON){
				//Save Old bird's position to be cleared later
				bird_x_old = bird_x;
				//Clear Bird's Old Position
				charSPACE(bird_x_old,bird_y);
				//Update Bird Location depending on boundary
				if(bird_x<1){
					wholeScreen(CLEAR,PAGEOFF);
					printTooHigh();
					wholeScreen(CLEAR,PAGEOFF);
					break;
				}
				else bird_x--;
			}
			if(ACT2_BUTTON) break; //Exit Game
		}
			
		//Condition when bird collides with obstacle
		if( ((obstacle_col <= CHAR_INT*3)&&(bird_x >= obstacle_height)) ){
			printColiisonMessage();
			wholeScreen(CLEAR,PAGEOFF);
			break;
		}	
		
		//Create new obstacle once it passes through screen
		if(obstacle_col < CHAR_INT){
			charCLEAROBSTACLE(CHAR_INT);
			obstacle_col = INIT_COL+CHAR_INT*6;	
			obstacle_height = 2 + rand()%4;
		}
		
		//Timer that controls bird drop movement
		if(time==0){
			//Reset timer to 1 sec
			time = 1;
			//Record Bird's Old Position
			bird_x_old = bird_x;
			//Clear Old Bird's Position
			charSPACE(bird_x_old,bird_y);
			//Move Bird Down 
			bird_x++;
		}
		
		//Ball drawn to Screen
		charSPACE(bird_x_old,bird_y);
		charBall(bird_x,bird_y);
		
		//Obstacle Drawn to Screen
		obstacle_col_old = obstacle_col;
		charCLEAROBSTACLE(obstacle_col_old);
		obstacle_col-=CHAR_INT;
		printObstacles(obstacle_height, obstacle_col);
		
		_delay_ms(200);

	}


}
