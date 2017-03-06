#include <string>

#ifndef TOWER_H
#define TOWER_H

class Tetronimo;
class Tower
{
private:
	static const int BUCKET_WIDTH = 12;
	static const int BUCKET_HEIGHT = 25;
	static const int MATRIX_SIZE = 5;
	static const int SINGLE_LINE_SCORE = 40;
	static const int DOUBLE_LINE_SCORE = 100;
	static const int TRIPLE_LINE_SCORE = 300;
	static const int TETRIS_SCORE = 1200;
	int score, level, grandTotalLinesCleared;
public:
	Tower();
	void clearScreen();
	void checkLines();
	void add(Tetronimo * toAdd);
	void display(Tetronimo * toDisplay);
	char bucket[BUCKET_WIDTH][BUCKET_HEIGHT];
	char tmpBucket[BUCKET_WIDTH][BUCKET_HEIGHT];
	void initializeTemporaryBucket(char* tmpShape);
	void addScore(int scoringValue, int level);
	void printBottomRow();	// prints the bottom row
	int getScore(void);		// returns the score as an int
	int getLevel(void);		// returns the level as an int
	int getTotalClearedLines(void);	// returns the total number of lines cleared
	void showStats(void);	// shows lines cleared, level, and score
//	int score, level, grandTotalLinesCleared;	// incremented every time you get a tetris
};

#endif