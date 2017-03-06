#ifndef TIMER_H
#define TIMER_H
#include <ctime>
#include <chrono>

class Timer
{
public:
	clock_t start; 
	Timer();	// constructor
	
	/* Function prototyping */
	void clearScreen(void);		// Changed to be platform independent
	void resetTimer(void);	// Changed to use the global Timer object delcared above
	double getElapsedTime(void);
};

#endif