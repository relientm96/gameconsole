/*------INFO--------*/
/*Name: Matthew Yong*/

/*--------Function Prototypes----------*/

//Initialization Functions
void initialize_backLight();
void initialize_Buttons();
void initialize_LOWLED();
void init_ButtonInterrupt();
void init_TimerInterrupt();
void init_Master();
void init_LCD();
void init_BattCheck();
void init_All();

//Menu Screen Displays
void printWelcome();
void printBrightnessInstructions();
void printGameMenu();
void printCursor(byte cursor_page);

//Menu Display Functions
void welcome_page();
void brightness_page();

//Games
void etchASketch();
void pong();
void guess();

//Etch a Sketch
void printEtchOpening();

//For Pong
void pongOpening();
void playerOneWins();
void playerTwoWins();
void charPlayerOneBar(byte text_page, byte text_column);
void charPlayerTwoBar(byte text_page, byte text_column);
void printPlayerOneBar(byte text_page);
void printPlayerTwoBar(byte text_page);
void printPauseMessage(byte p1, byte p2);
byte printAIselect();

//For Guess
void guessCursor(byte column);
void printChoices();
void printRightAnswer(byte score);
void printWrongAnswer(byte answer);
void printWinGuess();
void printGuessOpening();
void printMontyHall(byte selected);
void GameOver();

//For Flappy Bird
void flappyBird();
void flappyBirdOpening();
void printObstacles(byte height, byte column); 
void charCLEAROBSTACLE(byte obstacle_col_old);
void printColiisonMessage();
void countDown();
void printTooHigh();

//Battery 
void printBatteryLow(); 

/*---Helper Functions---*/
//For LCD Interfacing via SPI
void LCD_tx(byte tx_byte, byte CD_mode);
byte SPI_Exchange(byte data);
void select_column(byte column);
void select_page (byte page);
void wholeScreen(uint16_t load, byte clear);
void clearFrameBuffer();
void LCD_test(byte row, byte column);

/*--Additional Helper Functions--*/
//Bit Reversal 
byte bit_Reverse(byte b);

