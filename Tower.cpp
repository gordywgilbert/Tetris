#pragma once
#include "stdafx.h"
#include "Shapes.h"
#include "Tetris.h"
#include "Tetronimo.h"
#include "Tower.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <conio.h>

/* Initialize an empty Tower object */
Tower::Tower()
{
	for (int i = 0; i < BUCKET_WIDTH; i++) {
		for (int j = 0; j < BUCKET_HEIGHT; j++) {
			bucket[i][j] = ' ';
		}
	}
}

/* Tower object destructor */
Tower::~Tower()
{}

void Tower::checkLines()
{
	bool fail = false;
	int totalCleared = 0;
	int linesCleared[BUCKET_HEIGHT];
	char tmpLine[BUCKET_WIDTH];
	char tmpBucket[BUCKET_WIDTH][BUCKET_HEIGHT];
	for (int i = 0; i<BUCKET_WIDTH; i++){
		for (int j = 0; j<BUCKET_HEIGHT; j++){
			tmpBucket[i][j] = ' ';
		}
	}
	for (int j = 0; j < BUCKET_HEIGHT; j++){
		fail = false;
		for (int i = 0; i< BUCKET_WIDTH; i++){
			if (bucket[i][j] != 'X'){
				fail = true;
				tmpLine[i] = ' ';
			}
			else{
				tmpLine[i] = 'X';
			}
		}
		if (!fail){
			linesCleared[j] = 1;
			totalCleared++;
		}
		else{
			linesCleared[j] = 0;
		}
	}
	if (totalCleared > 0){
		for (int p = 178; p>175; p--){
			clearScreen();
			for (int j = 0; j<BUCKET_HEIGHT; j++){
				std::cout << "#";
				if (linesCleared[j] == 1){
					for (int i = 0; i<BUCKET_WIDTH; i++){
						//std::cout << char(p);
						if (totalCleared == 4 && i == 3){
							// user got a tetris
						}
					}
				}
				else{
					for (int i = 0; i<BUCKET_WIDTH; i++){
						std::cout << bucket[i][j];
					}
				}
				std::cout << "#";
				std::cout << std::endl;
			}
			for (int i = 0; i < BUCKET_WIDTH; i++) {
				std::cout << "#";
			}
			std::cout << std::endl;
			timer_reset();
			while (timer_elapsed()<.5){ ; }	// waits until a half a second has passed
		}
		int offset = 0;
		for (int j = (BUCKET_HEIGHT - 1); j >= 0; j--){
			if (linesCleared[j]){
				offset++;
			}
			else{
				for (int i = 0; i<BUCKET_WIDTH; i++){
					tmpBucket[i][j + offset] = bucket[i][j];
				}
			}
		}

		for (int i = 0; i<BUCKET_WIDTH; i++){
			for (int j = 0; j<BUCKET_HEIGHT; j++){
				bucket[i][j] = tmpBucket[i][j];
			}
		}

	}
}

/* Add a Tetronimo to the bucket and check to see if any lines are cleared or the bucket is filled */
void Tower::add(Tetronimo * toAdd)
{
	for (int i = 0; i<MATRIX_SIZE; i++){
		for (int j = 0; j<MATRIX_SIZE; j++){
			if (toAdd->shape[i][j] == 'X'){
				bucket[toAdd->x + i][toAdd->y + j] = toAdd->shape[i][j];
			}
		}
	}
	checkLines();
	if (toAdd->y < 1){
		clearScreen();
		std::cout << "You Lose!" << std::endl;
		std::cout << std::endl << std::endl;
		system("PAUSE");
		exit(1);
	}
}

/* Display the bucket */
void Tower::display(Tetronimo * toDisplay)
{
	bool displayChar = true;
	char tmpBucket[BUCKET_WIDTH][BUCKET_HEIGHT];
	for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			if ((toDisplay->shape[i][j] == 'X') &&
				(toDisplay->x + i >= 0) &&
				(toDisplay->x + i<BUCKET_WIDTH) &&
				(toDisplay->y + j >= 0) &&
				(toDisplay->y + j<BUCKET_HEIGHT)) {
				tmpBucket[toDisplay->x + i][toDisplay->y + j] = toDisplay->shape[i][j];
			}
		}
	}
	for (int j = 0; j < BUCKET_HEIGHT; j++){
		std::cout << "#";
		for (int i = 0; i < BUCKET_WIDTH; i++){
			displayChar = true;
			if (tmpBucket[i][j] == 'X'){
				std::cout << tmpBucket[i][j];
				displayChar = false;
			}
			if (displayChar) {
				std::cout << bucket[i][j];
			}
		}
		std::cout << "#";
		std::cout << std::endl;
	}
	for (int i = 0; i < BUCKET_WIDTH + 2 ; i++) { // the BUCKET_WIDTH+2 is for the walls 
		std::cout << "#";
	}
	std::cout << std::endl;
}