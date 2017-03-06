#include "stdafx.h"
#include "Timer.h"

#include <cstdlib>
#include <ctime>
#include <windows.h>

/* default constructor, uses the current system clock as a start time*/
Timer::Timer()
{
	start = clock();	// start = current clock time
}

/* resets the start to the current clock time instead of calling a new constructor, which would consume more resources */
void Timer::resetTimer()
{
	start = clock();	// reset the clock's start time
}

/* returns the time elapsed since the (current time - the start time)/ CLOCKS_PER_SEC, cast to a double */
double Timer::getElapsedTime()
{
	return (double)(clock() - start) / CLOCKS_PER_SEC;	// return the elapsed time since the last time the timer was reset
}