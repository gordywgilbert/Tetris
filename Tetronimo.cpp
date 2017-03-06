#include "stdafx.h"
#include "Tetris.h"
#include "Shapes.h"
#include "Tetronimo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <conio.h>

Tetronimo::Tetronimo(Tower * tow)
{
	srand((unsigned)time(NULL));	// initialize random seed once.
	nextUp = randInt(1, NUM_SHAPE_TYPES);			// generate a random number that is used to determine the shape
	x = 3;							// set initial x value for the block
	y = -1;							// set initial y value for the block
	tower = tow;					// save the values to the memory location for tower
	setBlock(randInt(1, NUM_SHAPE_TYPES) % NUM_SHAPE_TYPES);	// create a block based on the random number
}

/* Destructor to free up memory */
Tetronimo::~Tetronimo()
{}

/* Function for creating a new Tetronimo and choosing the next Tetronimo */
void Tetronimo::setBlock(int nextBlockNumber)
{
	for (int j = 0; j < MATRIX_SIZE; j++){
		for (int k = 0; k < MATRIX_SIZE; k++){
			shape[j][k] = shapesArray[nextUp][j][k];	// sets the shape array to the values stored in the nextUp array
		}
	}
	nextUp = nextBlockNumber;		// stores the number used to generate the next block when a block is created
	x = 5;							// set the x value for the next shape
	y = -1;							// set the y value for the next shape
}

/* Drops the Tetronimo one cell if the cell isn't occupied or out of bounds */
void Tetronimo::drop()
{
	bool droppable = true;
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			if (shape[i][j] == 'X'){
				if ((tower->bucket[i + x][j + y + 1] == 'X') ||
					((j + y + 1) >= BUCKET_HEIGHT)) {
					tower->add(this);
					setBlock(randInt(1, NUM_SHAPE_TYPES));
					droppable = false;
				}
			}
		}
	}
	if (droppable){ y++; }
}

/* Moves the Tetronimo one cell to the right if the cell isn't occupied or out of bounds */
void Tetronimo::moveRight()
{
	bool canMoveRight = true;
	for (int i = 0; i<MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			if (shape[i][j] == 'X'){
				if ((tower->bucket[i + x + 1][j + y] == 'X') ||
					((i + x + 1)>(BUCKET_WIDTH - 1))) {	// if the shape hits the right wall or an X
					canMoveRight = false;
				}
			}
		}
	}
	if (canMoveRight){ x++; }
}

/* Moves the Tetronimo one cell to the left if the cell isn't occupied or out of bounds */
void Tetronimo::moveLeft()
{
	bool canMoveLeft = true;
	for (int i = 0; i<MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			if (shape[i][j] == 'X'){
				if ((tower->bucket[i + x - 1][j + y] == 'X') ||
					((i + x - 1) < 0)) {			// if the shape hits the left wall or an X
					canMoveLeft = false;
				}
			}
		}
	}
	if (canMoveLeft){ x--; }
}

/* Rotates the block to the left if the space isn't occupied  */
void Tetronimo::rotateLeft()
{
	bool canRotateLeft = true;
	char tmpShape[MATRIX_SIZE][MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			tmpShape[i][j] = shape[j][MATRIX_SIZE - i];	// Opposite of rotating Right
		}
	}
	// see if the character stored at the tower pointer is able to rotate
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			if (tmpShape[i][j] == 'X'){
				if ((tower->bucket[i + x][j + y] == 'X') ||	
					(i + x < 0) || (i + x >(BUCKET_WIDTH - 1)) ||
					(j + y >(BUCKET_HEIGHT - 1))) {
					canRotateLeft = false;
				}
			}
		}
	}
	if (canRotateLeft){
		for (int i = 0; i < MATRIX_SIZE; i++){
			for (int j = 0; j<MATRIX_SIZE; j++){
				shape[i][j] = tmpShape[i][j];
			}
		}
	}
}

/* Rotates the block to the right if the space isn't occupied */
void Tetronimo::rotateRight()
{
	bool canRotateRight = true;
	char tmpShape[MATRIX_SIZE][MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			tmpShape[i][j] = shape[MATRIX_SIZE - j][i];	// Opposite of rotating left
		}
	}
	// see if the character stored at the tower pointer is able to rotate
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			if (tmpShape[i][j] == 'X'){
				if ((tower->bucket[i + x][j + y] == 'X') ||
					(i + x < 0) || (i + x >(BUCKET_WIDTH - 1)) ||
					(j + y >(BUCKET_HEIGHT - 1))) {
					canRotateRight = false;
				}
			}
		}
	}
	if (canRotateRight){
		for (int i = 0; i < MATRIX_SIZE; i++){
			for (int j = 0; j<MATRIX_SIZE; j++){
				shape[i][j] = tmpShape[i][j];
			}
		}
	}
}