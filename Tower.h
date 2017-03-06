#include <string>

#ifndef TOWER_H
#define TOWER_H

class Tetronimo;
class Tower
{
private:
	/* Constant variables that will never be changed, and can only be accessed by the class. */
	static const int BUCKET_WIDTH = 12;
	static const int BUCKET_HEIGHT = 25;
	static const int MATRIX_SIZE = 5;
	static const int SINGLE_LINE_SCORE = 40;
	static const int DOUBLE_LINE_SCORE = 100;
	static const int TRIPLE_LINE_SCORE = 300;
	static const int TETRIS_SCORE = 1200;
	/* Lines added to calculate scoring during, and at the end of the game */
	int score, level, grandTotalLinesCleared;
public:
	Tower();
	void clearScreen();	// Uses a windows function to clear the screen. by using a function like this it will be easier to adapt to other platforms
	void checkLines();	// checks for a line clear
	void add(Tetronimo * toAdd);	// adds a tetronimo to the bucket
	void display(Tetronimo * toDisplay);	// displays the tetronimo in the bucket along with the rest of the bucket
	void initializeTemporaryBucket(char* tmpShape);
	void addScore(int scoringValue, int level);	// adds to the total score based on a simple calculation
	void printBottomRow();	// prints the bottom row
	void showStats(void);	// shows lines cleared, level, and score
	int getScore(void);		// returns the score as an int
	int getLevel(void);		// returns the level as an int
	int getTotalClearedLines(void);	// returns the total number of lines cleared
	char bucket[BUCKET_WIDTH][BUCKET_HEIGHT];	// declares a public 2d array of characters, with the dimensions of BUCKET_WIDTH and BUCKET_HEIGHT
	char tmpBucket[BUCKET_WIDTH][BUCKET_HEIGHT];	// allocates memory for the tmpBucket 2d array of characters
};

#endif