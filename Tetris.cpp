#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <random>

using namespace std;

/* Constants for heights and widths */
const int CONSOLE_WIDTH = 400, CONSOLE_HEIGHT = 400;	// console window (400x400)
const int BUCKET_HEIGHT = 25, BUCKET_WIDTH = 12;		// bucket size (25x12)

/* Bucket array 25x12 */
char bucket[BUCKET_HEIGHT][BUCKET_WIDTH];	// allocate memory for the bucket array

/* Public variables of type bool */
bool gameLost = false;
bool shapeStuck = false;

/* Public variables of type int */
int shapeTopLeftX = 0;
int shapeTopLeftY = 5;
int oldTopLeftX = 0;
int oldTopLeftY = 5;

/* TetrisShape Class Definition*/
class TetrisShape {
public:
	void createTetronimo(int shapeType);
	char shapeArray[4][4];
private:
	enum Shapes { Box, Line, S, Z, L, J, T };
};

//function declarations
void setConsole();	// positions
void setCursorTo(int x, int y);
void initializeBucket();
void drawBucket();
void getRandNum(int seed);
void drawShape();
void updateBucket(TetrisShape shape, int x, int y);
void processDownArrow(TetrisShape& tetrishape);
void removeTrail(int x, int y);
void moveShape(TetrisShape shape);
int getRandomNumber();
void dropShape(TetrisShape shape);
void inline timeControl(int timer);
void stuckCheck(TetrisShape shape);
void dropNewShape();

int wmain()
{
	srand((unsigned int) time(0));
	initializeBucket();

	//creates a shape
	TetrisShape shape, temp;
	shape.createTetronimo(getRandomNumber());

	while (!gameLost) {
		temp = shape;
		drawBucket();
		
		// testing out a shape dropping
		shapeTopLeftX++; // shape falls, need to check and see if it is stuck still. 
		/*
		processDownArrow(shape);
		if (shapeStuck) {
			shape.createTetronimo(getRandomNumber());

			system("Pause");
		}
		*/
		// end test excerpt

		updateBucket(temp, shapeTopLeftX, shapeTopLeftY);
		drawBucket();
		timeControl(350);
		if (!shapeStuck) {
			removeTrail(oldTopLeftX, oldTopLeftY);
		}
		else {
			dropNewShape();
		}
		//system("Pause");

	}
	system("Pause");
}

/* setConsole() - http://www.cplusplus.com/forum/beginner/1481/
   set the console's width and height for windows users, 
   solves issues with the console being redrawn. */
void setConsole() {
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, CONSOLE_WIDTH, CONSOLE_HEIGHT, true);
}

/* Gets a random number using the <random> library */
int getRandomNumber() {
	int randomNumber = rand() % 7 + 1;
	return randomNumber;
}

// from module 4
void setCursorTo(int x, int y) {
	HANDLE handle;
	COORD position;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(handle, position);
}

// draw the bucket, created for module 4
void initializeBucket() {
	for (int i = 0; i < BUCKET_HEIGHT; i++) {	// using the constant BUCKET_HEIGHT declared above
		for (int j = 0; j < BUCKET_WIDTH; j++) {// using the constant BUCKET_WIDTH declared above
			if (j == 0 || j == 11 || i == 24) {	// columns 1 and 12 and the bottom row (i==24) will be filled
				bucket[i][j] = '#';
			}
			else if (bucket[i][j] == 'X') {	// if the bucket's x,y coords are occupied, do not modify
				continue;
			}
			else { // if neither condition exists, place an empty char ' '
				bucket[i][j] = ' ';	
			}
		}
	}
}

void drawBucket() {
	setConsole();
	setCursorTo(0, 1);
	initializeBucket();
	for (int i = 0; i < BUCKET_HEIGHT; i++) {
		for (int j = 0; j < BUCKET_WIDTH; j++) {
			cout << bucket[i][j];
			if (j == (BUCKET_WIDTH-1)) cout << endl;	// draws the second column then begins again
		}
	}
}

// create the various Tetronimo shapes shown at http://www.tetrisfriends.com/help/tips_appendix.php#tetristerminology
void TetrisShape::createTetronimo(int shapeNumber) {
	if (shapeNumber == 1) {		// O-Tetronimo
		shapeArray[0][0] = ' ';   shapeArray[1][0] = 'X';   shapeArray[2][0] = 'X';   shapeArray[3][0] = ' ';
		shapeArray[0][1] = ' ';   shapeArray[1][1] = 'X';   shapeArray[2][1] = 'X';   shapeArray[3][1] = ' ';
		shapeArray[0][2] = ' ';   shapeArray[1][2] = ' ';   shapeArray[2][2] = ' ';   shapeArray[3][2] = ' ';
		shapeArray[0][3] = ' ';   shapeArray[1][3] = ' ';   shapeArray[2][3] = ' ';   shapeArray[3][3] = ' ';
	}
	else if (shapeNumber == 2) {	// I-Tetronimo
		shapeArray[0][0] = ' ';   shapeArray[1][0] = 'X';   shapeArray[2][0] = ' ';   shapeArray[3][0] = ' ';
		shapeArray[0][1] = ' ';   shapeArray[1][1] = 'X';   shapeArray[2][1] = ' ';   shapeArray[3][1] = ' ';
		shapeArray[0][2] = ' ';   shapeArray[1][2] = 'X';   shapeArray[2][2] = ' ';   shapeArray[3][2] = ' ';
		shapeArray[0][3] = ' ';   shapeArray[1][3] = 'X';   shapeArray[2][3] = ' ';   shapeArray[3][3] = ' ';
	}
	else if (shapeNumber == 3) {	// S-Tetronimo
		shapeArray[0][0] = ' ';   shapeArray[1][0] = 'X';   shapeArray[2][0] = 'X';   shapeArray[3][0] = ' ';
		shapeArray[0][1] = 'X';   shapeArray[1][1] = 'X';   shapeArray[2][1] = ' ';   shapeArray[3][1] = ' ';
		shapeArray[0][2] = ' ';   shapeArray[1][2] = ' ';   shapeArray[2][2] = ' ';   shapeArray[3][2] = ' ';
		shapeArray[0][3] = ' ';   shapeArray[1][3] = ' ';   shapeArray[2][3] = ' ';   shapeArray[3][3] = ' ';
	}
	else if (shapeNumber == 4) {	// Z-Tetronimo
		shapeArray[0][0] = 'X';   shapeArray[1][0] = 'X';   shapeArray[2][0] = ' ';   shapeArray[3][0] = ' ';
		shapeArray[0][1] = ' ';   shapeArray[1][1] = 'X';   shapeArray[2][1] = 'X';   shapeArray[3][1] = ' ';
		shapeArray[0][2] = ' ';   shapeArray[1][2] = ' ';   shapeArray[2][2] = ' ';   shapeArray[3][2] = ' ';
		shapeArray[0][3] = ' ';   shapeArray[1][3] = ' ';   shapeArray[2][3] = ' ';   shapeArray[3][3] = ' ';
	}
	else if (shapeNumber == 5) {	// L-Tetronimo
		shapeArray[0][0] = ' ';   shapeArray[1][0] = 'X';   shapeArray[2][0] = ' ';   shapeArray[3][0] = ' ';
		shapeArray[0][1] = ' ';   shapeArray[1][1] = 'X';   shapeArray[2][1] = ' ';   shapeArray[3][1] = ' ';
		shapeArray[0][2] = ' ';   shapeArray[1][2] = 'X';   shapeArray[2][2] = 'X';   shapeArray[3][2] = ' ';
		shapeArray[0][3] = ' ';   shapeArray[1][3] = ' ';   shapeArray[2][3] = ' ';   shapeArray[3][3] = ' ';

	}
	else if (shapeNumber == 6) {	// J-Tetronimo
		shapeArray[0][0] = ' ';   shapeArray[1][0] = 'X';   shapeArray[2][0] = ' ';   shapeArray[3][0] = ' ';
		shapeArray[0][1] = ' ';   shapeArray[1][1] = 'X';   shapeArray[2][1] = ' ';   shapeArray[3][1] = ' ';
		shapeArray[0][2] = 'X';   shapeArray[1][2] = 'X';   shapeArray[2][2] = ' ';   shapeArray[3][2] = ' ';
		shapeArray[0][3] = ' ';   shapeArray[1][3] = ' ';   shapeArray[2][3] = ' ';   shapeArray[3][3] = ' ';
	}
	else if (shapeNumber == 7) { // T-Tetronimo
		shapeArray[0][0] = 'X';   shapeArray[1][0] = 'X';   shapeArray[2][0] = 'X';   shapeArray[3][0] = ' ';
		shapeArray[0][1] = ' ';   shapeArray[1][1] = 'X';   shapeArray[2][1] = ' ';   shapeArray[3][1] = ' ';
		shapeArray[0][2] = ' ';   shapeArray[1][2] = ' ';   shapeArray[2][2] = ' ';   shapeArray[3][2] = ' ';
		shapeArray[0][3] = ' ';   shapeArray[1][3] = ' ';   shapeArray[2][3] = ' ';   shapeArray[3][3] = ' ';
	}
}

void updateBucket(TetrisShape shape, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			bucket[i + x][j + y] = shape.shapeArray[i][j];
		}
	}
	oldTopLeftX = shapeTopLeftX;
	oldTopLeftY = shapeTopLeftY;
}

void removeTrail(int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (bucket[i + x][j + y] != '#') {
				bucket[i + x][j + y] = ' ';
			}
		}
	}
}

void inline timeControl(int timer) {
	Sleep(timer);
}

void processDownArrow(TetrisShape& tetrisShape) {
	stuckCheck(tetrisShape);
	if (!shapeStuck) {
		shapeTopLeftX++;
	}
	else {
		dropNewShape();
	}
}

void stuckCheck(TetrisShape shape) {
	for (int i = 0; i < BUCKET_HEIGHT; i++) {
		for (int j = 0; j < BUCKET_WIDTH; j++) {
			if ((shape.shapeArray[i][j] != ' ') || (shape.shapeArray[i][j] != 'X')) {
				if (j > 0 && j < 24){
					shapeStuck = true;
					return;
				}
			}
		}
	}
	//shapeStuck = false;
}

void dropNewShape() {
	TetrisShape shape;
	shape.createTetronimo(getRandomNumber());
	shapeTopLeftX = 0;
	shapeTopLeftY = 5;
	oldTopLeftX = 0;
	oldTopLeftY = 5;
	shapeStuck = false;
}