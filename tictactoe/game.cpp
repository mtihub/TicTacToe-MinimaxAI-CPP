#include "game.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <limits>


Game::Game() : gameBoard(), human(), currentTurn('X'), winner('N') {
	initializeGame();
}

void Game::initializeGame() {
	std::cout.flush();
	system("clear");

	std::cout << "\n\n***************************************************************\n";
	std::cout << "               Welcome to the game of Tic Tac Toe\n";
	std::cout << "***************************************************************\n\n";

	choosePlayer();
}

void Game::choosePlayer() {
	std::cout << "Do you want to play as \"X\" or \"O\"? ";

	human.takeSignInput();
	ai.setSign( (human.getSign() == 'X') ? 'O' : 'X' );
}


void Game::play() {
	while (winner == 'N') {
		gameBoard.printBoard();

		if (currentTurn == ai.getSign()) {
			ai.makeMove(gameBoard);
			
		}
		else {
			human.makeMove(gameBoard);
		}

		toggleTurn();
		winner = gameBoard.checkWinner();
	}

	gameBoard.printBoard();
	gameOver();

}


void Game::toggleTurn() {
	currentTurn = (currentTurn == 'X') ? 'O' : 'X';
}

void Game::gameOver() {
	std::cout << "\n\n***** Game Over *****\n" << std::endl;
	if (winner == 'X' || winner == 'O') {
		std::cout << winner << " has won!" << std::endl;
	}
	else if (winner == 'D') {
		std::cout << "Game is a draw." << std::endl;
	}
	std::cout << "\n*********************\n\n" << std::endl;
	
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	char c = getchar();
	std::cin.ignore();
}

char Game::getWinner() {
	return winner;
}
