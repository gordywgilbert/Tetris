#ifndef TETRONIMO_H
#define TETRONIMO_H

#include "Shapes.h"
#include "Tower.h"

class Tower;
class Shapes;
class Tetronimo : public Shapes
{
private:
	static const int MATRIX_SIZE = 5;
	static const int BUCKET_HEIGHT = 25;
	static const int BUCKET_WIDTH = 12;
	static const int NUM_SHAPE_TYPES = 7;
public:
	Tetronimo(Tower * tow);
	void setBlock(int nextBlockNumber);
	void rotateLeft();
	void rotateRight();
	void drop();
	void moveLeft();
	void moveRight();
	void storeShape(char* tmpShape);
	int selectRandomShape();
	char((shape)[MATRIX_SIZE])[MATRIX_SIZE];
	char tmpShape[MATRIX_SIZE][MATRIX_SIZE];
	int x; int y; int nextUp;
	Tower * tower;
};

#endif