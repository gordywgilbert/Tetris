#ifndef SHAPES_H
#define SHAPES_H

class Tetronimo;
class Shapes
{
private:
	static const int MATRIX_SIZE = 5;		// the size of the shape matrix 5x5 currently
	static const int NUM_SHAPE_TYPES = 7;	// the number of shape types
public:
	Shapes();	// default constructor for the shape object
	char(((shapesArray)[NUM_SHAPE_TYPES])[MATRIX_SIZE])[MATRIX_SIZE];	// creates a 7*5*5 array of characters in memory that stores the shape types.
};

#endif