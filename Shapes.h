#pragma once
#include "Tetris.h"

class Shapes
{
public:
	static int const NUM_SHAPE_TYPES = 7;	// Stores the number of different shapes
	static int const MATRIX_SIZE = 5;		// Stores the number of elements in the square matrix
	static int const BUCKET_HEIGHT = 25;	// Stores the bucket height as an int
	static int const BUCKET_WIDTH = 12;		// Stores the bucket width as an int
	Shapes();
	char(((shapesArray)[NUM_SHAPE_TYPES])[MATRIX_SIZE])[MATRIX_SIZE];
};