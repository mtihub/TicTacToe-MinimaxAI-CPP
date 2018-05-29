#ifndef __MINIMAX_MOVE_H__
#define __MINIMAX_MOVE_H__

class MinimaxMove {
private:
	int row;
	int col;
	int score;

public:
	MinimaxMove();
	MinimaxMove(int score);
	MinimaxMove(int x, int y, int score);

	void setRow(int i);
	void setCol(int j);
	void setScore(int sc);
	int getRow();
	int getCol();
	int getScore();
};

#endif