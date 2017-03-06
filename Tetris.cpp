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
#include "Shapes.h"
#include "Tetris.h"
#include "Tetronimo.h"
#include "Tower.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

static clock_t start = (clock_t)0;
void timer_reset()
{
	start = clock();
}
double timer_elapsed()
{
	return (double)(clock() - start) / CLOCKS_PER_SEC;
}
int randInt(int a, int b)
{
	return rand() % b + a;
}

void clearScreen()
{
	system("CLS");
}

void setConsole() {
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, CONSOLE_WIDTH, CONSOLE_HEIGHT, true);
}

int main()
{
	setConsole();
	bool done = false;
	char chr = ' ';
	Tower tower;
	bool dropped;
	double droptime;
	Tetronimo curBlock(&tower);	// pass the tower object by reference
	while (!done){
		timer_reset();	// reset the timer
		dropped = 0;	// initialize number of dropped blocks
		droptime = .2;	// initialize speed of blocks falling
		while (timer_elapsed() < droptime){		// while less time than droptime has passed
			if (_kbhit()) {
				chr = _getch();	// get the user keyboard input
			}
			else {
				chr = ' ';	// if no key is entered then chr = ' '
			}
			switch (chr) {
			case KEY_LEFT:
				curBlock.moveLeft();
				clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			case KEY_RIGHT:
				curBlock.moveRight();
				clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			case KEY_DOWN:
				curBlock.drop();
				clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			case KEY_UP:
				curBlock.rotateLeft();
				clearScreen();
				tower.display(&curBlock);	// current block is passed by reference
				break;
			}
		}
		clearScreen();
		curBlock.drop();
		tower.display(&curBlock);
	}
	return 0;
}