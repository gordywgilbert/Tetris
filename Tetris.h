#pragma once
#include "Shapes.h"

#define KEY_UP 72		// used for switch case below, up arrow is 72
#define KEY_DOWN 80		// used for switch case below, down arrow is 80
#define KEY_LEFT 75		// used for switch case below, left arrow is 75
#define KEY_RIGHT 77	// used for switch case below, right arrow is 77

static int const NUM_SHAPE_TYPES = 7;	// Stores the number of different shapes
static int const MATRIX_SIZE = 5;		// Stores the number of elements in the square matrix
static int const BUCKET_HEIGHT = 25;	// Stores the bucket height as an int
static int const BUCKET_WIDTH = 12;		// Stores the bucket width as an int
static int const CONSOLE_WIDTH = 300;	// Stores the console width variable
static int const CONSOLE_HEIGHT = 380;	// Stores the console width variable

/* Class prototyping */
class Tower;	
class Shapes;
class Tetronimo;

/* Function prototyping */
void clearScreen();
void timer_reset();
void setConsole();
double timer_elapsed();
int randInt(int a, int b);