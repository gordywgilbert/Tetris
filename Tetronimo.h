#pragma once
#include "Shapes.h"
#include "Tetris.h"
#include "Tetronimo.h"
#include "Tower.h"

class Tetronimo : public Shapes
{
public:
	Tetronimo(Tower * tow);
	~Tetronimo();
	void setBlock(int nextBlockNumber);
	void rotateLeft();
	void rotateRight();
	void drop();
	void moveLeft();
	void moveRight();
	char((shape)[MATRIX_SIZE])[MATRIX_SIZE];
	int x;
	int y;
	int nextUp;
	Tower * tower;
};