/*********************************************************\
| Creator: Michael Hamilton, Dec 22 2005                  |
| Project Info: ASCII Tetris                              |
| Notes: Feel free to redistribute, keep this note intact |
| with the original creator information, but do whatever  |
| you want with this code just don't claim ownership of   |
| the code base.                                          |
| http://www.mutedvision.net      maxmike@gmail.com       |
\*********************************************************/

#include "stdafx.h"
#include "Tetris.h"
#include "Tetronimo.h"
#include "Timer.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <conio.h>
#include <windows.h>

#define KEY_UP 72		// used for switch case below, up arrow is 72
#define KEY_DOWN 80		// used for switch case below, down arrow is 80
#define KEY_LEFT 75		// used for switch case below, left arrow is 75
#define KEY_RIGHT 77	// used for switch case below, right arrow is 77

/* Currently requires windows to work, 
*		Resizes the window to the parameters provided by the function.
*		The code is from module 4's instructions
*
*	CONSOLE_WIDTH - Console window width in pixels
*  CONSOLE_HEIGHT - Console window height in pixels
*/
void setConsole() {
	const int CONSOLE_WIDTH = 300;	// Stores the console width variable
	const int CONSOLE_HEIGHT = 380;	// Stores the console width variable
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, CONSOLE_WIDTH, CONSOLE_HEIGHT, true);
}

int main()
{
	setConsole();	// creates and positions the console window
	Timer timer;	// creates an instance of the timer object
	Tower tower = Tower();	// calls the default constructor for the Tower class
	bool gameLost = false;	// gameLost is a variable that is used to determine when the while loop should break
	char chr = ' ';	// sets the value for the variable that stores user input to ' '

	bool dropped = false;
	double droptime = .3;	// initialize the droptime for the blocks
	Tetronimo curBlock(&tower);	// pass the tower object by reference
	while (!gameLost){
		timer.resetTimer();	// reset the timer
		dropped = false;	// initialize number of dropped blocks
		droptime = .2;	// initialize speed of blocks falling
		while (timer.getElapsedTime() < droptime){		// while less time than droptime has passed
			if (_kbhit()) {
				chr = _getch();	// get the user keyboard input
			}
			else {
				chr = ' ';	// if no key is entered then chr = ' '
			}
			switch (chr) {
			case KEY_LEFT:
				curBlock.moveLeft();
				tower.clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			case KEY_RIGHT:
				curBlock.moveRight();
				tower.clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			case KEY_DOWN:
				curBlock.drop();
				tower.clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			case KEY_UP:
				curBlock.rotateLeft();
				tower.clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			}
		}
		tower.clearScreen();
		curBlock.drop();
		tower.display(&curBlock);
	}
	return 0;
}