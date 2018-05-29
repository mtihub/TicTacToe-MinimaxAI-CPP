#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"
#include "human.h"
#include "ai.h"
#include "minimaxMove.h"

class Game {
private:
	Board gameBoard;
	Human human;
	AI ai;
	char currentTurn;
	char winner;

	void initializeGame();
	void choosePlayer();
	void toggleTurn();
	void gameOver();

public:
	Game();
	void play();
	char getWinner();
};

#endif
