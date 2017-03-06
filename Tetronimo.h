#ifndef TETRONIMO_H
#define TETRONIMO_H

#include "Shapes.h"
#include "Tower.h"

class Tower;
class Shapes;
class Tetronimo : public Shapes
{
private:
	/* constant values that will only be accessed by the class and won't change */
	static const int MATRIX_SIZE = 5;
	static const int BUCKET_HEIGHT = 25;
	static const int BUCKET_WIDTH = 12;
	static const int NUM_SHAPE_TYPES = 7;
public:
	Tower * tower;			// pointer to tower variable of type Tower
	Tetronimo(Tower * tow);	// default constructor
	void setBlock(int nextBlockNumber);	// creates a new block object and initializes the choice for the next shape
	void drop();			// drops the shape one coordinate
	void moveLeft();		// move the shape to the left one position if the space isn't out of bounds or occuppied
	void moveRight();		// move the shape one to the right if the space isn't out of bounds or occupied
	void storeShape(char* tmpShape);	// stores the temporary shape in the new position
	void rotateLeft();		// rotates the block to the left, if possible
	//void rotateRight();	// rotates the block to the right (currently unused)
	int selectRandomShape();// generates a number between 1 and 7, which is used to determine what shape is chosen when using the constructor.

	/* publicly visible and modifiable variables, scope should be smaller but time was of the essence */
	int x; int y; int nextUp;

	char((shape)[MATRIX_SIZE])[MATRIX_SIZE];	// array of shapes
	char tmpShape[MATRIX_SIZE][MATRIX_SIZE];	// temporary array to store the shape array
};

#endif