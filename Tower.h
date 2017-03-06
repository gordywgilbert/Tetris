#pragma once
#include "Shapes.h"
#include "Tetris.h"
#include "Tetronimo.h"
#include "Tower.h"

class Tower
{
public:
	Tower();
	~Tower();
	void checkLines();
	void add(Tetronimo * toAdd);
	void display(Tetronimo * toDisplay);
	char((bucket)[BUCKET_WIDTH])[BUCKET_HEIGHT];
};