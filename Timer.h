#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <chrono>

class Timer
{
public:
	clock_t start;	// publicly visible variable that may be modified outside of its class
	Timer();		// default constructor, uses now() to get the current clock cycle
	void clearScreen(void);		// Changed to be platform independent
	void resetTimer(void);		// Changed to use the global Timer object delcared above
	double getElapsedTime(void);// returns the elapsed time based on the system clock
};

#endif