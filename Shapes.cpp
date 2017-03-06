#include "stdafx.h"
#include "Shapes.h"

/* Default constructor for a shape, adds the correct values to the array that are going to be accsessed later */
Shapes::Shapes()
{
	char tmpShapesArray[NUM_SHAPE_TYPES][MATRIX_SIZE][MATRIX_SIZE] = {
		// Begin T Shape
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ',
		' ', 'X', 'X', 'X', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', ' ', ' ', ' ', ' ',
		// Begin I Shape
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		// Begin J shape
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', 'X', 'X', ' ', ' ',
		' ', ' ', ' ', ' ', ' ',
		// Begin L Shape
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', ' ', 'X', ' ', ' ',
		' ', ' ', 'X', 'X', ' ',
		' ', ' ', ' ', ' ', ' ',
		// Begin Square Shape
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ',
		' ', 'X', 'X', ' ', ' ',
		' ', 'X', 'X', ' ', ' ',
		' ', ' ', ' ', ' ', ' ',
		// Begin Z shape
		' ', ' ', ' ', ' ', ' ',
		' ', 'X', 'X', ' ', ' ',
		' ', ' ', 'X', 'X', ' ',
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ',
		// S Shape
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', 'X', 'X', ' ',
		' ', 'X', 'X', ' ', ' ',
		' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' '
	};
	for (int i = 0; i < NUM_SHAPE_TYPES; i++) {				// iterates through the number of shape types
		for (int j = 0; j < MATRIX_SIZE; j++) {				// outside loop to iterate through MATRIX_SIZE x MATRIX_SIZE matrix
			for (int k = 0; k < MATRIX_SIZE; k++) {			// inside loop to iterate through MATRIX_SIZE x MATRIX_SIZE matrix
				shapesArray[i][j][k] = tmpShapesArray[i][j][k];	// store the information from shapesArray into tmpShapesArray
			}
		}
	}
};