#include "human.h"
#include <iostream>

Human::Human() {}

Human::Human(char c) : sign(c) {}

void Human::setSign(char c) {
    sign = c;
}

char Human::getSign() {
    return sign;
}

void Human::takeSignInput() {
    char humanSignInput;
    bool isValid = false;
    while (!isValid) {
        std::cin >> humanSignInput;
        if (humanSignInput == 'x' || humanSignInput == 'X' || humanSignInput == 'o' || humanSignInput == 'O') {
            isValid = true;
        }
        else {
            std::cout << "Invalid input." << std::endl;
        }
    }

    if (humanSignInput == 'x') {
        humanSignInput = 'X';
    }
    else if (humanSignInput == 'o') {
        humanSignInput = 'O';
    }

    sign = humanSignInput;
}

void Human::makeMove(Board& gameBoard) {
    std::vector<int> humanMove = getHumanMove(gameBoard);
    gameBoard.fillSquare(humanMove.at(0), humanMove.at(1), sign);
}


std::vector<int> Human::getHumanMove(Board& gameBoard) {
        std::vector<int> moveVec;
        std::cout << "***** Your Turn *****" << std::endl;

        bool isFilled = true;
        while (isFilled) {
            std::cout << "Choose row coordinate (1, 2, 3): ";
            takeValidInput(moveVec, 0);
            std::cout << "Choose column coordinate (1, 2, 3): ";
            takeValidInput(moveVec, 1);

            if (gameBoard.get(moveVec.at(0), moveVec.at(1)) == 'N') {
                isFilled = false;
            }
            else {
                 std::cout << "The square is already taken. Choose an empty square.\n" << std::endl;
            }
        }

        return moveVec;
}

void Human::takeValidInput(std::vector<int>& moveVec, int index) {
	int input;
    bool isValid = false;
    while (!isValid) {
        std::cin >> input;
        if (input == 1 || input == 2 || input == 3) {
        	isValid = true;
        }
        else {
            std::cout << "Invalid input." << std::endl;
        }
	}

    if (moveVec.size() < 2) {
        moveVec.push_back(input-1);
    }
    else {
        moveVec.at(index) = input-1;
    }
}
