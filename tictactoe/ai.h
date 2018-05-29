#ifndef __AI_H__
#define __AI_H__

#include "board.h"
#include "minimaxMove.h"
#include <vector>

class AI {
private:
	char aiSign;
	char humanSign;

	std::vector<int> getWinningMove(Board& gameBoard);
	MinimaxMove minimax(Board& gameBoard, char player);	
public:
	AI();
	AI(char c);
	void setSign(char c);
	char getSign();
	void makeMove(Board& gameBoard);
};

#endif