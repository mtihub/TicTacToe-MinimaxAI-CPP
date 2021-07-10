var user   = getUserSign();		// Human
var ai     = getAISign(user);	// AI

var currentTurn = "X";	// First turn is X
var totalTurn   = 0;	// Initiate total turns

// Get box elements
var boxElements = document.getElementsByClassName("box");

// Create a board to hold the game status
var board = createBoard();

// Add event listener to the elements
for (var i = 0; i < boxElements.length; i++) {
    boxElements[i].addEventListener("mouseenter", function(e) { 
    	(e.target).style.backgroundColor = "#827f60";
    });
    boxElements[i].addEventListener("mouseout", function(e) { 
    	(e.target).style.backgroundColor = "transparent";
    });
    
    boxElements[i].addEventListener("click", function(e) { 
    	console.log(e); 
    	boxClicked(e.target); 
    });


}


// Check if AI goes first
var isAITurn = (ai == "X") ? true : false;

var counter = 0;

// If the AI is player X, make a turn
if (isAITurn) {
	aiTurn();
}


// Click function
// After the human clicks a square, this function runs
// At the end it calls the aiTurn() to make the AI's next move
function boxClicked(elementClicked) {
	console.log(elementClicked);	
	console.log("Box clicked");

	// Fill box
	elementClicked.innerHTML = currentTurn;			// Fill Box
	elementClicked.style.pointerEvents = "none";	// Disable Click on this box
	
  	toggleTurn();	// Toggle the current turn
  	totalTurn++;	// Increment Total Turns
  	updateBoard();  // Update the board status

  	// Check if the game is over
  	var status = checkGameStatus();
  	if (status != "NO_VAL") {
  		gameOver(status);
  		return;
  	}

  	// If it was human's turn, next turn is the AI's
  	if (isAITurn == false) {
  		isAITurn = true;
  		aiTurn();
  	}

  	isAITurn = false;

  	console.log("Counter: " + counter);
  	counter = 0;
}


// AI function 
function aiTurn() {
	var winningMove = getWinningMove(ai);
	if (winningMove.isWinning == true) {
		boxElements[winningMove.boxIndex].click();
	}
	else {
		var bestMove = minimax(ai);
		boxElements[bestMove.boxIndex].click();
	}
}

//-------------------------------------------------------------------------------------------
// Minimax 
//-------------------------------------------------------------------------------------------

function minimax(player) {
	counter++;
	//console.log("Doing minimax");
	var boardStatus = checkGameStatus();

	if (boardStatus == "X" || boardStatus == "O") {
		var currentScore = (ai == boardStatus) ? 10 : -10;
		var currentMove = {x: -1, y: -1, boxIndex: -1, score: currentScore};
		return currentMove;
	}
	else if (boardStatus == "DRAW") {
		var currentMove = {x: -1, y: -1, boxIndex: -1, score: 0};
		return currentMove;
	}


	// Array that holds the current possible moves
	// It stores a move object. The object has indices and score.
	// At the end, the move with the highest score is chosen
	var possibleMoves = [];

	// Loop through the empty boxes and call minimax until the terminating result is found
	var boxElementIndex = 0;
	for (var i = 0; i < 3; i++) {
		for (var j = 0; j < 3; j++) {
			// If the square is empty, calculate the score of that move
			if (board[i][j] == "") {
				// move object
				var move = {
					x: i,
					y: j,
					boxIndex: boxElementIndex,
					score: 0
				};

				// Fill the board with current move
				board[i][j] = player;
				
				// If the player is AI, the next move is human's. So call minimax with human as the player
				// Else the other way around
				if (player == ai) {
					var temp = minimax(user);
					move.score = temp.score;
				}
				else {
					var temp = minimax(ai);
					move.score = temp.score;	
				}

				// Store the move in the array
				possibleMoves.push(move);

				// Remove the move from the board
				board[i][j] = "";	
			}

			boxElementIndex++;
		}
	}


	// Calculate the best move
	var bestPossibleMove = 0;

	// If the player is AI, it will pick the move with the maximum score
	if (player == ai) {
		var bestScore = -100000;
		for (var i = 0; i < possibleMoves.length; i++) {
			if (possibleMoves[i].score > bestScore && possibleMoves[i].score != -999) {
				bestPossibleMove = i;
				bestScore = possibleMoves[i].score;
			}
		}
	}

	// Human will choose the move with the minimum score
	else {
		var bestScore = 100000;
		for (var i = 0; i < possibleMoves.length; i++) {
			if (possibleMoves[i].score < bestScore && possibleMoves[i].score != -999) {
				bestPossibleMove = i;
				bestScore = possibleMoves[i].score;
			}
		}
	}
	
	return possibleMoves[bestPossibleMove];
}


// Function to get an immediate winning move
function getWinningMove(player) {
	var boxElementIndex = 0;
	for (var i = 0; i < 3; i++) {
		for (var j = 0; j < 3; j++) {
			if (board[i][j] == "") {
				board[i][j] = player;
				var status = checkGameStatus();
				if (status == player) {
					var winningMove = {isWinning: true, x: i, y: j, boxIndex: boxElementIndex};
					return winningMove;
				}
				board[i][j] = "";
			}

			boxElementIndex++;
		}
	}

	return {isWinning: false, x: -1, y: -1, boxIndex: -1};
}



// This function checks the board[][] and returns the status
function checkGameStatus() {
	if (board[0][0] != "") {
		if ( ((board[0][0] == board[0][1]) && (board[0][0] == board[0][2]))  ||
			 ((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]))  ||
			 ((board[0][0] == board[1][0]) && (board[0][0] == board[2][0])) ) {
			//gameWon();
			return board[0][0];
		}
	}

	if (board[1][0] != "") {
		if ( ((board[1][0] == board[1][1]) && (board[1][0] == board[1][2])) ) {
			//gameWon();
			return board[1][0];
		}
	}

	if (board[2][0] != "") {
		if ( ((board[2][0] == board[2][1]) && (board[2][0] == board[2][2])) ||
			 ((board[2][0] == board[1][1]) && (board[2][0] == board[0][2])) ) {
			//gameWon();
			return board[2][0];
		}
	}

	if (board[0][1] != "") {
		if ( ((board[0][1] == board[1][1]) && (board[0][1] == board[2][1])) ) {
			//gameWon();
			return board[0][1];
		}
	}

	if (board[0][2] != "") {
		if ( ((board[0][2] == board[1][2]) && (board[0][2] == board[2][2])) ) {
			//gameWon();
			return board[0][2];
		}
	}

	var turnsTaken = 0;
	for (var i = 0; i < 3; i++) {
		for (var j = 0; j < 3; j++) {
			if (board[i][j] != "") {
				turnsTaken++;
			}
		}
	}
	if (turnsTaken == 9) {
		return "DRAW";
	}

	return "NO_VAL";
}




// Game over displays
function gameOver(stat) {
	disableAll();
	if (stat == "X" || stat == "O") {
		document.getElementById("gameover").innerHTML = stat + " Wins!";
	}
	else {
		document.getElementById("gameover").innerHTML = "It's a Draw";
	}

	setTimeout(function() {alert("Game Over");}, 400);
}


//-------------------------------------------------------------------------------------------
// Utility Functions
//-------------------------------------------------------------------------------------------

// Function to get player input
function getUserSign() {
	var input = prompt("Choose sign: X or O?");
	while (input != "X" && input != "O" && input != "x" && input != "o" ) {
		input = prompt("Choose sign: X or O?");
	}

	if (input == "x") input = "X";
	else if (input == "o") input = "O";

	return input;
}

// Function that determines AI sign based on player sign
function getAISign(userSign) {
	if (userSign == "X") {
		return "O";
	} 
	else {
		return "X";
	}
}

// Function to create a 3x3 board
function createBoard() {
	var board = [["", "", ""], ["", "", ""], ["", "", ""]];
	return board;
}

// Function that updates the board after every click
function updateBoard() {
	var boxElementIndex = 0;
	for (var i = 0; i < 3; i++) {
		for (var j = 0; j < 3; j++) {
			board[i][j] = boxElements[boxElementIndex].innerHTML;
			boxElementIndex++;
		}
	}
}


// Disable all the squares by making then un-clickable
function disableAll() {
	for (var i = 0; i < boxElements.length; i++) {
    	boxElements[i].style.pointerEvents = "none";
	}
}

// Toggle turn. Called after each button click
function toggleTurn() {
	if (currentTurn == "X") 
		currentTurn = "O";
	else
		currentTurn = "X";
}

// Get text of a square from the square's id
function getText(boxId) {
	return document.getElementById(boxId).innerHTML;
}











