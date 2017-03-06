#include "stdafx.h"
#include "Tetronimo.h"
#include "Tower.h"
#include "Timer.h"

#include <windows.h>
#include <iostream>
#include <string>

/* Initialize an empty Tower object */
Tower::Tower()
{
	grandTotalLinesCleared = 0;
	level = 1;
	score = 0;
	for (int i = 0; i < BUCKET_WIDTH; i++) {
		for (int j = 0; j < BUCKET_HEIGHT; j++) {
			bucket[i][j] = ' ';
		}
	}
}

/* returns the player's score */
int Tower::getScore() {
	return score;
}

/* returns the player's current level */
int Tower::getLevel() {
	return level;
}

/* returns the total number of all lines cleared */
int Tower::getTotalClearedLines() {
	return grandTotalLinesCleared;
}

/* prints the bottom row of # instead of using the clearline method to*/
void Tower::printBottomRow() {
	for (int i = 0; i < BUCKET_WIDTH + 2; i++) {
		std::cout << "#";
	}
}

void Tower::initializeTemporaryBucket(char* tmpBucket) {
	for (int i = 0; i<BUCKET_WIDTH; i++){
		for (int j = 0; j<BUCKET_HEIGHT; j++){
			tmpBucket[i*MATRIX_SIZE + j] = ' ';
		}
	}
}

/* function to check lines for lines to be cleared, also handles scoring */
void Tower::checkLines()
{
	Timer gameTimer;
	int totalCleared = 0;
	bool fail = false;
	bool tetrisScored = false;
	int linesCleared[BUCKET_HEIGHT];	// declares an array, linesCleared with BUCKET_HEIGHT elements
	char tmpLine[BUCKET_WIDTH];			// declares a character array of BUCKET_WIDTH
	level = (grandTotalLinesCleared / 10) + 1;
	initializeTemporaryBucket(*tmpBucket);

	for (int j = 0; j < BUCKET_HEIGHT; j++){
		fail = false;
		for (int i = 0; i< BUCKET_WIDTH; i++){
			if (bucket[i][j] != 'X'){	// if the element at bucket[i][j] isnt an X then store ' ' at tmpLine[i]
				fail = true;
				tmpLine[i] = ' ';
			}
			else{
				tmpLine[i] = 'X';		// if the element at bucket[i][j] is an X then store 'X' at tmpLine[i] 
			}
		}
		if (fail){
			linesCleared[j] = 0;
		}
		else{
			linesCleared[j] = 1;		// stores 1 at linesCleared[j]
			totalCleared++;				// increments the total number of lines cleared
			grandTotalLinesCleared++;
		}
	}
	if (totalCleared > 0){
		// The ascii codes used for the loop are visible at http://www.cplusplus.com/doc/ascii/ 
		// it contains the char code 178 (B2 in hex), so it starts there for the fade
		for (int p = 178; p>175; p--) {			// Three characters that are used to fade away.
			for (int j = 0; j<BUCKET_HEIGHT; j++){
				std::cout << "#";				// print the left wall of the bucket of the bucket
				if (linesCleared[j] == 1) {		// is this line cleared?
					for (int i = 0; i<BUCKET_WIDTH; i++){
						std::cout << char(p);	// prints out either char(178), char(177) or char(176)
						if (totalCleared == 4 && i == 3){
							addScore(TETRIS_SCORE, level);	// adds the score for a tetris
							tetrisScored = true;
						}
					}
				}
				else {
					for (int i = 0; i<BUCKET_WIDTH; i++) { // the BUCKET_WIDTH+2 is for the walls 
						std::cout << bucket[i][j];
					}
				}
				std::cout << "#" << std::endl;	// prints the right wall
			}
			printBottomRow();
			std::cout << std::endl;
			gameTimer.resetTimer();
			while (gameTimer.getElapsedTime() < .5){ ; }	// waits until a half a second has passed
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
		// only executes if a tetris score hasn't already been added for the lines removed
		if (!tetrisScored) {
			if (totalCleared == 3) {
				addScore(TRIPLE_LINE_SCORE, level);
			}
			else if (totalCleared == 2) {
				addScore(DOUBLE_LINE_SCORE, level);
			}
			else if (totalCleared == 1) {
				addScore(SINGLE_LINE_SCORE, level);
			}
		}
	}
}

/* adds the (scoringValue * level) to the variable score */
void Tower::addScore(int scoringValue, int level) {
	switch (scoringValue) {
		case TETRIS_SCORE:
			score += (TETRIS_SCORE * level);
			break;
		case TRIPLE_LINE_SCORE:
			score += (TRIPLE_LINE_SCORE * level);
			break;
		case DOUBLE_LINE_SCORE:
			score += (DOUBLE_LINE_SCORE * level);
			break;
		case SINGLE_LINE_SCORE:
			score += (SINGLE_LINE_SCORE * level);
			break;
	}
}

/* displays the level, score, and total lines cleared */
void Tower::showStats() {
	std::cout << "Level:" << getLevel() << "    Score: " << getScore() << std::endl << "Total Lines Cleared: " << getTotalClearedLines();
}

/* eventually this should be replaced with a platform independent solution */
void Tower::clearScreen()
{
	system("CLS");	// Old windows specific call to clear the screen.
}

/* Add a Tetronimo to the bucket and then check to see if any lines are cleared or the bucket is filled */
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
	if (toAdd->y < 1){	// character is above the rim of the bucket
		clearScreen();	// call to the clearScreen() function
		std::cout << "You Lose!" << std::endl;	// output you lose
		std::cout << std::endl << std::endl;	// add a few spaces
		showStats();	// display the stats for the game
		system("PAUSE");
		exit(1);	// exit the application with code 1, a clean exit
	}
}

/* Display the bucket */
void Tower::display(Tetronimo * toDisplay)
{
	bool displayChar = true;
	memset(tmpBucket, ' ', sizeof(tmpBucket)); // Fill the array with zeros
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
		std::cout << "#" << std::endl;
	}
	
	printBottomRow();	// prints the bottom row of #
	std::cout << std::endl;	//
	showStats();
}