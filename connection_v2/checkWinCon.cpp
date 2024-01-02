/*
This piece of code only contains the check win condition part, the full game flow should be like texts below:
(Suppose client has a "isReady" state declared in "info" (0 -> not ready, 1 -> ready)
	, and is turned from 0 -> 1 when Ready btn is clicked
	, and server keeps track of the ready list)

Server: 
	1) pair 2 random clients and removes them from ready list (turn 1 -> 0)
	2) Assign player 1 and player 2 to clients.
	3) Actually start the game. Server maintains a board.
	4) Check if one client disconnect, if so, announce win info to the other client and close game.
	5) Listen to client inputs and check win condition with code similar to that below. If game ended, address winner/loser and close game.
		5.1)
	
p.s. 
In client part, it is likely to use Gomoku code. 
However, since the code isn't merged with the client/server structure yet, the client will need to slightly tweek that code.
i.e. 
Add client name as "self", and compare it with currentPlayer before sending a move to server. 
	In line 254 of Gomoku.cpp, add a condition so that click only respond when currentPlayer == self.
	In line 272 of Gomoku.cpp, let board[][] be set to self instead of currentPlayer.
	After doing so, send <j, i, player> to server.
In addition, in client, maybe add an updateBoard() and put before drawBoard() in run() for handling receiving the other client's board click.
	In updateBoard(), it should first check if player == self. 
	If it is, do nothing.
	If not, it should read and add the other client's click pos to board. Server should send the j i for it to update (set board to player::properPlayer).
	After that, tunCount++, and change currentPlayer to self.

*/
#include <stdio.h>

#define SIZE 15

// Function to check the win condition in Gomoku
int checkWinCondition(char board[SIZE][SIZE], int row, int col, char player) {
    // Check horizontally
    int count = 0;
    for (int i = col - 4; i <= col + 4; ++i) {
        if (i >= 0 && i < SIZE && board[row][i] == player) {
            count++;
            if (count == 5) {
                return 1; // Player wins horizontally
            }
        } else {
            count = 0;
        }
    }

    // Check vertically
    count = 0;
    for (int i = row - 4; i <= row + 4; ++i) {
        if (i >= 0 && i < SIZE && board[i][col] == player) {
            count++;
            if (count == 5) {
                return 2; // Player wins vertically
            }
        } else {
            count = 0;
        }
    }

    // Check diagonally (top-left to bottom-right)
    count = 0;
    for (int i = -4; i <= 4; ++i) {
        int r = row + i;
        int c = col + i;
        if (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == player) {
            count++;
            if (count == 5) {
                return 3; // Player wins diagonally
            }
        } else {
            count = 0;
        }
    }

    // Check diagonally (top-right to bottom-left)
    count = 0;
    for (int i = -4; i <= 4; ++i) {
        int r = row - i;
        int c = col + i;
        if (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == player) {
            count++;
            if (count == 5) {
                return 4; // Player wins diagonally
            }
        } else {
            count = 0;
        }
    }

    return 0; // No win condition
}

// Function to initialize the board
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the current state of the board
void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char board[SIZE][SIZE];
    
    initializeBoard(board);
    
    int row, col;
    char player;
    int curPlayer; // This may not be necessary, as client keeps track of it already.
    int turnCount = 1; // This part needs to be modified, so that server's turnCount + 1 after receive from click board info from client.
    
    
    while (1) {
    
    	
    	// Set proper curPlayer for this turn.
    	// This may not be necessary, as client keeps track of it already.
    	curPlayer = (turnCount % 2 == 0) ? 2 : 1;
    	printf("Turn count: %d, player: %d\n", turnCount, curPlayer);
    	
        // Get user input for row, col, and player
        printf("Enter row, col, and player (e.g., 3 5 X): ");
        scanf("%d %d %c", &row, &col, &player);

	// Check player == X / O / ?
	// This code may not be necessay assuming the client sends correct message.
	if (player != 'X' && player != 'O') {
	    printf("Invalid player. Player should be O or X\n");
	    continue;
	}	
	
	// Check player input eligibility.
	// This code may not be necessay if we let client maintain which message to send.
	if ((curPlayer == 1 && player == 'O') || (curPlayer == 2 && player == 'X')) {
	    printf("Invalid input. Wrong player.\n");
	    continue;
	} 
        // Check if the input is valid
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid input. Row and col must be between 0 and %d.\n", SIZE - 1);
            continue;
        }

        // Check if the cell is already occupied
        // This code may not be necessay since we've prevented the client from clicking on occupied already.
        if (board[row][col] != ' ') {
            printf("Cell already occupied. Choose a different position.\n");
            continue;
        }

        // Make the move
        board[row][col] = player;

        // Print the current state of the board
        printf("Current Board:\n");
        printBoard(board);

        // Check for win condition
        int result = checkWinCondition(board, row, col, player);
        if (result == 1) {
            printf("Player %c wins horizontally!\n", player);
            break;
        } else if (result == 2) {
            printf("Player %c wins vertically!\n", player);
            break;
        } else if (result == 3 || result == 4) {
            printf("Player %c wins diagonally!\n", player);
            break;
        }
        
        turnCount+=1;
    }

    return 0;
}

