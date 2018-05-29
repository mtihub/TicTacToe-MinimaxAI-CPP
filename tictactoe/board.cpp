#include "board.h"
#include <iostream>

Board::Board() : board{ {'N', 'N', 'N'}, {'N', 'N', 'N'}, {'N', 'N', 'N'} } {}
//Board::Board() : board{ {'X', 'O', 'N'}, {'O', 'N', 'X'}, {'N', 'X', 'O'}  } {}

void Board::fillSquare(int i, int j, char player) {
	board[i][j] = player;
}

char Board::get(int i, int j) {
	return board[i][j];
}

char Board::checkWinner() {
	if (board[0][0] != 'N') {
		if ( ((board[0][0] == board[0][1]) && (board[0][0] == board[0][2]))  ||
			 ((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]))  ||
			 ((board[0][0] == board[1][0]) && (board[0][0] == board[2][0])) ) {
			return board[0][0];
		}
	}

	if (board[1][0] != 'N') {
		if ( ((board[1][0] == board[1][1]) && (board[1][0] == board[1][2])) ) {
			return board[1][0];
		}
	}

	if (board[2][0] != 'N') {
		if ( ((board[2][0] == board[2][1]) && (board[2][0] == board[2][2])) ||
			 ((board[2][0] == board[1][1]) && (board[2][0] == board[0][2])) ) {
			return board[2][0];
		}
	}

	if (board[0][1] != 'N') {
		if ( ((board[0][1] == board[1][1]) && (board[0][1] == board[2][1])) ) {
			return board[0][1];
		}
	}

	if (board[0][2] != 'N') {
		if ( ((board[0][2] == board[1][2]) && (board[0][2] == board[2][2])) ) {
			return board[0][2];
		}
	}

	int turnsTaken = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != 'N') {
				turnsTaken++;
			}
		}
	}
	if (turnsTaken == 9) {
		return 'D';
	}

	return 'N';
}


void Board::printLine(char sign, int lineNum, int colNum) {
	switch (lineNum) {
		case 1:
			if (sign == 'X') {
				std::cout << "*.  .* ";
			}
			else if (sign == 'O') {
				std::cout << "  **   ";
			}
			else {
				std::cout << "       ";
			}
			break;

		case 2:
			if (sign == 'X') {
				std::cout << "  **   ";
			}
			else if (sign == 'O') {
				std::cout << " *  *  ";
			}
			else {
				std::cout << "       ";
			}
			break;
		
		case 3:
			if (sign == 'X') {
				std::cout << " .**.  ";
			}
			else if (sign == 'O') {
				std::cout << " *  *  ";
			}
			else {
				std::cout << "       ";
			}
			break;	
		
		case 4:
			if (sign == 'X') {
				std::cout << "*    * ";
			}
			else if (sign == 'O') {
				std::cout << "  **   ";
			}
			else {
				std::cout << "       ";
			}
			break;
	}

	if (colNum != 2) {
		std::cout << "|";
	}

}

void Board::printBoard() {
	std::cout.flush();
	system("clear");

	std::cout << "\n\n";
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 3; j++) {
				printLine(board[i][j], k+1, j);
			}
			std::cout << std::endl;
		}

		if (i != 2) {
			std::cout<< "-----------------------" << std::endl;
		}
	}
	std::cout << "\n\n";
}