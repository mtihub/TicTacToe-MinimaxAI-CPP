#include "ai.h"

AI::AI() {}

AI::AI(char c) {
	aiSign = c;
	humanSign = (c == 'X') ? 'O' : 'X';
}

void AI::setSign(char c) {
	aiSign = c;
	humanSign = (c == 'X') ? 'O' : 'X';
}

char AI::getSign() {
	return aiSign;
}

void AI::makeMove(Board& gameBoard) {
	std::vector<int> winningMove = getWinningMove(gameBoard);
	if (winningMove.at(0) != -1) {
		gameBoard.fillSquare(winningMove.at(0), winningMove.at(1), aiSign);
	}
	else {
		MinimaxMove bestMove = minimax(gameBoard, aiSign);
		gameBoard.fillSquare(bestMove.getRow(), bestMove.getCol(), aiSign);
	}
}


std::vector<int> AI::getWinningMove(Board& gameBoard) {
	std::vector<int> moveVec;

	char hasWinner;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gameBoard.get(i,j) == 'N') {
				gameBoard.fillSquare(i, j, aiSign);
				hasWinner = gameBoard.checkWinner();
				if (hasWinner == aiSign) {
					moveVec.push_back(i);
					moveVec.push_back(j);
					return moveVec;
				}
				gameBoard.fillSquare(i, j, 'N');
			}
		}
	}

	moveVec.push_back(-1);
	moveVec.push_back(-1);
	return moveVec;
}


MinimaxMove AI::minimax(Board& gameBoard, char player) {
	int status = gameBoard.checkWinner();
	if (status == 'X' || status == 'O') {
		MinimaxMove minimaxMove;
		minimaxMove.setScore( (status == aiSign) ? 10 : -10 );
		return minimaxMove;
	}
	else if (status == 'D') {
		MinimaxMove minimaxMove(0);
		return minimaxMove;
	}

	std::vector<MinimaxMove> movesVec;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gameBoard.get(i,j) == 'N') {
				gameBoard.fillSquare(i, j, player);

				MinimaxMove minimaxMove(i, j, 0);
				if (player == aiSign) {
					int minimaxScore = minimax(gameBoard, humanSign).getScore();
					minimaxMove.setScore(minimaxScore);
				}
				else {
					int minimaxScore = minimax(gameBoard, aiSign).getScore();
					minimaxMove.setScore(minimaxScore);
				}	
				movesVec.push_back(minimaxMove);

				gameBoard.fillSquare(i, j, 'N');
			}
		}
	}

	int bestMoveAt = -1;
	if (player == aiSign) {
		int bestScore = -10000;
		for (int i = 0; i < movesVec.size(); i++) {
			if (movesVec.at(i).getScore() > bestScore) {
				bestMoveAt = i;
				bestScore = movesVec.at(i).getScore();
			}
		}
	}
	else {
		int bestScore = 10000;
		for (int i = 0; i < movesVec.size(); i++) {
			if (movesVec.at(i).getScore() < bestScore) {
				bestMoveAt = i;
				bestScore = movesVec.at(i).getScore();
			}
		}
	}

	return movesVec.at(bestMoveAt);
}