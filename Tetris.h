#ifndef TETRIS_H
#define TETRIS_H

/* This class is probably a unecessary, but it was interesting to learn about */
class Tetris
{
public:	
	void clearScreen();		// Changed back to be platform dependent (for clarity, 50 new lines didn't work well)
	void restartTimer();	// Changed to use the global Timer object delcared above
	void setConsole();		// sets the console (game) window's height, width and other attributes
	double getElapsedTime();	// returns the elapsed time calculated by the number of clock cycles since the function was last called
};

#endif