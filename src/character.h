/*-----Character Function Prototype Declarations-----*/

//Declarations for all of the characters and numbers used to draw on LCD

/*-----------Character Functions---------------*/

//Character Transmit Function
void charLetter(byte text_page, byte text_column, byte a0, byte a1, byte a2, byte a3, byte a4, byte a5, byte a6, byte a7);

//MISC
void charSPACE(byte text_page, byte text_column);
void charCURSOR(byte text_page, byte text_column);
void charBall(byte text_page, byte text_column);

//Alphabets
void charA(byte text_page, byte text_column);
void charB(byte text_page, byte text_column);
void charC(byte text_page, byte text_column);
void charD(byte text_page, byte text_column);
void charE(byte text_page, byte text_column);
void charF(byte text_page, byte text_column);
void charG(byte text_page, byte text_column);
void charH(byte text_page, byte text_column);
void charI(byte text_page, byte text_column);
void charJ(byte text_page, byte text_column);
void charK(byte text_page, byte text_column);
void charL(byte text_page, byte text_column);
void charM(byte text_page, byte text_column);
void charN(byte text_page, byte text_column);
void charO(byte text_page, byte text_column);
void charP(byte text_page, byte text_column);
void charQ(byte text_page, byte text_column);
void charR(byte text_page, byte text_column);
void charS(byte text_page, byte text_column);
void charT(byte text_page, byte text_column);
void charU(byte text_page, byte text_column);
void charV(byte text_page, byte text_column);
void charW(byte text_page, byte text_column);
void charX(byte text_page, byte text_column);
void charY(byte text_page, byte text_column);
void charZ(byte text_page, byte text_column);
//Numbers
void char1(byte text_page, byte text_column);
void char2(byte text_page, byte text_column);
void char3(byte text_page, byte text_column);
void char4(byte text_page, byte text_column);
void char5(byte text_page, byte text_column);
void char6(byte text_page, byte text_column);
void char7(byte text_page, byte text_column);
void char8(byte text_page, byte text_column);
void char9(byte text_page, byte text_column);
void drawNums(byte text_page, byte text_column, byte num);
