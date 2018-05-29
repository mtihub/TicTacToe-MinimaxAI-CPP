#ifndef __BOARD_H__
#define __BOARD_H__

class Board {
private:
	char board[3][3];
	
	void printLine(char sign, int lineNum, int colNum);

public:
	Board();
	void printBoard();
	void fillSquare(int i, int j, char player);
	char get(int i, int j);
	char checkWinner();
};

#endif
