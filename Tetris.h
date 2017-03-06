#ifndef TETRIS_H
#define TETRIS_H

class Tetris
{
public:	
	/* Function prototyping */
	void clearScreen();		// Changed to be platform independent
	void restartTimer();	// Changed to use the global Timer object delcared above
	void setConsole();
	double getElapsedTime();
};

#endif