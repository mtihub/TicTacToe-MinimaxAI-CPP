#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "board.h"
#include <vector>

class Human {
private:
	char sign;

	void takeValidInput(std::vector<int>& moveVec, int index);
	std::vector<int> getHumanMove(Board& gameBoard);

public:
	Human();
	Human(char c);
	void setSign(char c);
	char getSign();
	void takeSignInput();
	void makeMove(Board& gameBoard);
};


#endif
