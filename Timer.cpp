#include "stdafx.h"
#include "Timer.h"

#include <cstdlib>
#include <ctime>
#include <windows.h>

Timer::Timer()
{
	start = clock();
}

void Timer::resetTimer()
{
	start = clock();
}

double Timer::getElapsedTime()
{
	return (double)(clock() - start) / CLOCKS_PER_SEC;
}