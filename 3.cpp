#include <iostream>
#include <iomanip> // For setw
#include <cstdlib> // For system
#include <string>  // For string operations

#define width 50

using namespace std;

char board[3][3]; // Game board

// Initialize the game board
void initializeBoard() {
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

// Print the game board
void printBoard() {
    for(int i=0;i<3;i++){
    
    	for(int j=0;j<3;j++){
    		cout<<board[i][j];
    		if(j<2){
    			cout<<"  |";
			}
		}
		cout<<"\n";
		if(i<2){
			cout<<"---+---+---\n";
		}
	}
	
}


// Check if there is a winner
bool checkWin(char player) {
    // Check rows and columns
    for(int i = 0; i < 3; ++i) {
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) return true; // Check rows
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player) return true; // Check columns
    }
    // Check diagonals
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Check if the game is a draw
bool checkDraw() {
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(board[i][j] == ' ') return false; // If there is any empty space, it's not a draw
        }
    }
    return true; // All spaces are filled and no winner
}

// Main game loop
void playGame() {
    char currentPlayer = 'X';
    int row, col;
    bool gameEnded = false;

    initializeBoard();

    while(!gameEnded) {
        system("cls");

        cout << "Current Board:\n\n";
        printBoard();
        cout << "\n";

        // Player's turn
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        // Validate the move
        if(row < 1 || row > 3 || col < 1 || col > 3 || board[row-1][col-1] != ' ') {
            cout << "Invalid move! Try again.\n";
            system("pause");
            continue;
        }

        // Update the board
        board[row-1][col-1] = currentPlayer;

        // Check for win
        if(checkWin(currentPlayer)) {
            system("cls");
            cout << "Current Board:\n\n";
            printBoard();
            cout << "\n";
            cout << "Player " << currentPlayer << " wins!\n";
            gameEnded = true;
        } else if(checkDraw()) {
            system("cls");
            cout << "Current Board:\n\n";
            printBoard();
            cout << "\n";
            cout << "It's a draw!\n";
            gameEnded = true;
        } else {
            if(currentPlayer=='X'){
            	currentPlayer='Y';
			}
			else{
				currentPlayer='X';
			}
        }

        system("pause");
    }
}

int main() {
    char playAgain;

    do {
        system("cls");
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while(playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing!\n";

    return 0;
}

