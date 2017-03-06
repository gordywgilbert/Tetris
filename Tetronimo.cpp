#include "stdafx.h"
#include "Tetronimo.h"
#include <iostream>
#include <random>

/* Class constructor for Tetronimos.*/
Tetronimo::Tetronimo(Tower * tow)
{
	nextUp = selectRandomShape();	// generate a random number that is used to determine the shape
	x = 3;							// set initial x value for the block
	y = -1;							// set initial y value for the block
	tower = tow;					// save the values to the memory location for tower
	setBlock(selectRandomShape());	// create a block based on the random number
}

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

/* Drops the Tetronimo one cell if the cell 
*	isn't occupied and the coordinate isn't out of bounds */
void Tetronimo::drop()
{
	bool droppable = true;
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			if (shape[i][j] == 'X'){
				// tower gets dereferenced when -> is used and "tower->bucket" ends up being treated as (*tower).bucket
				if ((tower->bucket[i + x][j + y + 1] == 'X') ||
					((j + y + 1) >= BUCKET_HEIGHT)) {
					tower->add(this);
					setBlock(selectRandomShape());
					droppable = false;
				}
			}
		}
	}
	if (droppable){ y++; }
}

/* Moves the Tetronimo one cell to the right 
*	if the cell isn't occupied or out of bounds */
void Tetronimo::moveRight()
{
	bool canMoveRight = true;
	for (int i = 0; i<MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			if (shape[i][j] == 'X'){
				// tower gets dereferenced when -> is used and "tower->bucket" ends up being treated as (*tower).bucket
				if ((tower->bucket[i + x + 1][j + y] == 'X') ||
					((i + x + 1)>(BUCKET_WIDTH - 1))) {	// if the shape hits the right wall or an X
					canMoveRight = false;
				}
			}
		}
	}
	if (canMoveRight){ x++; }
}

/* Moves the Tetronimo one cell to the left if 
*	the cell isn't occupied or out of bounds */
void Tetronimo::moveLeft()
{
	bool canMoveLeft = true;
	for (int i = 0; i<MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			if (shape[i][j] == 'X'){
				// tower gets dereferenced when -> is used and "tower->bucket" ends up being treated as (*tower).bucket
				if ((tower->bucket[i + x - 1][j + y] == 'X') ||
					((i + x - 1) < 0)) {			// if the shape hits the left wall or an X
					canMoveLeft = false;
				}
			}
		}
	}
	if (canMoveLeft){ x--; }
}

/* Rotates the block to the left if the space isn't occupied   
*		9/8/15 Updated to use the storeShape function		   */
void Tetronimo::rotateLeft()
{
	bool canRotateLeft = true;
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			tmpShape[i][j] = shape[j][MATRIX_SIZE - i-1];	// Opposite of rotating Right
		}
	}
	// see if the character stored at the tower pointer is able to rotate
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			if (tmpShape[i][j] == 'X'){
				// tower gets dereferenced when -> is used and "tower->bucket" ends up being treated as (*tower).bucket
				if ((tower->bucket[i + x][j + y] == 'X') ||	
					(i + x < 0) || 
					(i + x >(BUCKET_WIDTH - 1)) ||
					(j + y >(BUCKET_HEIGHT - 1))) {
					canRotateLeft = false;
				}
			}
		}
	}
	if (canRotateLeft){
		storeShape(*tmpShape);
	}
}

/* Rotates the block to the right if the space isn't occupied 
 *		9/8/15 Updated to use the storeShape function		   */
void Tetronimo::rotateRight()
{
	bool canRotateRight = true;
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			tmpShape[i][j] = shape[MATRIX_SIZE - j-1][i];	// Opposite of rotating left
		}
	}
	// see if the character stored at the tower pointer is able to rotate
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			if (tmpShape[i][j] == 'X'){
				// tower gets dereferenced when -> is used and "tower->bucket" ends up being treated as (*tower).bucket
				if ((tower->bucket[i + x][j + y] == 'X') ||
					(i + x < 0) || 
					(i + x >(BUCKET_WIDTH - 1)) ||
					(j + y > (BUCKET_HEIGHT - 1))) {
					canRotateRight = false;
				}
			}
		}
	}
	if (canRotateRight){
		storeShape(*tmpShape);
	}
}

/* Stores the shape in tmpShape to the 2 dimensional shape 
*	array using math to access specific items in the tmpShape array. */
void Tetronimo::storeShape(char* tmpShape) {
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			shape[i][j] = tmpShape[i*MATRIX_SIZE + j];
		}
	}
}

/* Uses a random device to seed the generator, providing a better alternative to the rand() function */
int Tetronimo::selectRandomShape() {
	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> dist(0, 6); // distribute results between 0 and 6 inclusive.
	return dist(gen);
}