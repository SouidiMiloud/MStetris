#ifndef PLAYER_H
#define PLAYER_H

#include"io/Keyboard.h"
#include"Shape.h"
#include"gameobjects/Digit.h"

class Player
{
public:
	~Player();
	static void clearResources();

	static void play(Shape* shape);
	static void initializeNumber();
	static void renderScore();
	static void updateScore();
	static void endGame();
	static bool isGameOver();
	static void pauseGame();
	static void reset();

private:
	static int score;
	static bool pause;
	static bool gameOver;
	static int COUNTER_LEVEL_CHANGE;
	static int counterLevelChange;
	static const int DIFFERENCE_BETWEEN_TWO_LEVELS;
	static int level;
	static std::vector<Digit*> number;

	static void displayScore();
	static void manageLevel();
};

#endif // !PLAYER_H
