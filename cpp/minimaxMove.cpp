#include "minimaxMove.h"

MinimaxMove::MinimaxMove() : row(-1), col(-1), score(-1) {}
MinimaxMove::MinimaxMove(int sc) : row(-1), col(-1), score(sc) {}
MinimaxMove::MinimaxMove(int i, int j, int sc) : row(i), col(j), score(sc) {}

void MinimaxMove::setRow(int i) {
	row = i;
}

void MinimaxMove::setCol(int j) {
	col = j;
}

void MinimaxMove::setScore(int sc) {
	score = sc;
}

int MinimaxMove::getRow() {
	return row;
}

int MinimaxMove::getCol() {
	return col;
}

int MinimaxMove::getScore() {
	return score;
}