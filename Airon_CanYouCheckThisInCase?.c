#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constants
#define SIZE 4
#define UNO "('o')"
#define TRES "(-.-)"
#define DOS "(>u<)"
#define EMPTY "     "

//initialize grid to be empty
void initializeGrid(char grid[SIZE][SIZE][6]) {
	int i, j;
	//loop through the grid and set all positions to empty
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            strcpy(grid[i][j], EMPTY); //copy empty to each cell
        }
    }
    
} 

//print current state of the grid
void printGrid(char grid[SIZE][SIZE][6]) {
	int i, j;
	
    for (i = 0; i < SIZE; i++) { 			//loop through each row
        printf("+ --- + --- + --- + --- +\n"); 		//row separator
        for (j = 0; j < SIZE; j++) { 			//loop through each column
            printf("|");
            if (strcmp(grid[i][j], UNO) == 0) {		//print appropriate symbol and its color
            	printf("\x1b[32m%s\x1b[0m", UNO);	// green for UNO
			}
            else if (strcmp(grid[i][j], TRES) == 0){
            	printf("\x1b[34m%s\x1b[0m", TRES);	// blue for TRES
			}
            else {
            	printf("%s", EMPTY);			//print empty cell if a player didn't move there
			}
        }
        printf("|\n");
    }
    printf("+ --- + --- + --- + --- +\n");
    
}

//check if the board is full (no empty spaces left)
int CheckBoard(char grid[SIZE][SIZE][6]){
	
	int i, j;
	int IsFull = -1;	// IsFull signals whether board is full or not (1 for full, 0 for not)
	int count = 0; 		// counts cells that are not empty
	
	for (i = 0; i < SIZE; i++){
		for (j = 0; j < SIZE; j++){
			if (strcmp(grid[i][j], EMPTY) != 0){	//count cells that are not empty
				count++;
			}
		}
	}

	if (count == 16)				//if all cells are filled, return 1 (board is full)
		IsFull = 1;
	else
		IsFull = 0; 				//board is not full
	
	return IsFull; 
}

//check if a player has won
int CheckIfWin(char grid[SIZE][SIZE][6], char *Player) {
	
	int Win = 0; 
	
    if (strcmp(grid[0][0], Player) == 0 && strcmp(grid[0][1], Player) == 0 && strcmp(grid[0][2], Player) == 0 && strcmp(grid[0][3], Player) == 0) {		//check horizontal rows
        	Win = 1; 
			return Win;	
	}
    else if (strcmp(grid[3][0], Player) == 0 && strcmp(grid[3][1], Player) == 0 && strcmp(grid[3][2], Player) == 0 && strcmp(grid[3][3], Player) == 0) {
        	Win = 1; 
			return Win;	
	}

    
    if (strcmp(grid[0][0], Player) == 0 && strcmp(grid[1][1], Player) == 0 && strcmp(grid[2][2], Player) == 0 && strcmp(grid[3][3], Player) == 0) {		//check diagonally from top-left to bottom-right
    	Win = 1; 
		return Win;
	}
    else if (strcmp(grid[0][3], Player) == 0 && strcmp(grid[1][2], Player) == 0 && strcmp(grid[2][1], Player) == 0 && strcmp(grid[3][0], Player) == 0) { 	//check diagonally from top-right to bottom-left
    	Win = 1; 
		return Win;
	}
	
    return Win;		//return 0 if no win conditions yet
}

//game loop
int playGame() {
	
    char grid[SIZE][SIZE][6];
    initializeGrid(grid);
    srand(time(0));		//random number generator
    int over = 1; 
    
    while (over) {
    	
        printGrid(grid);
        int row, col;		//stores player's move

        do {			//TRES's turn
        	
        printf("TRES %s's turn. Enter row (0-3): ", TRES);
        scanf("%d", &row);
        
        printf("TRES %s. Enter column (0-3): ", TRES); 
        scanf("%d", &col); 
        
	        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || strcmp(grid[row][col], EMPTY) != 0) {		//validate move
	            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
	        		printf("Invalid move! Try again.\n");							//row or column out of bounds
				}
				else if (strcmp(grid[row][col], EMPTY) != 0) {
					printf("That position's been taken already. Please choose another one\n");	//position already taken
				}
	        }
	        
	    } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || strcmp(grid[row][col], EMPTY) != 0); 
        
        strcpy(grid[row][col], TRES);		//place TRES's symbol in chosen position
        
        if (CheckIfWin(grid, TRES)) {		//check if TRES wins
            printGrid(grid);
            printf("TRES%s wins!\n", TRES);
            over = 0; 				//game ends
            return over; 
        }
        
        printGrid(grid);			//print grid again

        if (CheckBoard(grid)) {			//check if grid is full
            printf("No more positions left!\nDOS%s wins!\n", DOS);
            over = 0;				//game ends
            return over;  
        }
        
        do {			//UNO's turn (same procedure)
        	
        printf("UNO %s's turn. Enter row (0-3): ", UNO);
        scanf("%d", &row);
        printf("UNO %s's turn. Enter column (0-3): ", UNO);
        scanf("%d", &col);
        
	        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || strcmp(grid[row][col], EMPTY) != 0) {
	            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
	        		printf("Invalid move! Try again.\n");
				}
				else if (strcmp(grid[row][col], EMPTY) != 0) {
					printf("That position's been taken already. Please choose another one\n");
				}
	        }
	        
			 
        } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || strcmp(grid[row][col], EMPTY) != 0); 
        
        strcpy(grid[row][col], UNO); 
        
        if (CheckIfWin(grid, UNO)) {		//check if UNO wins
            printGrid(grid);
            printf("UNO%s wins!\n", UNO);
            over = 0;				//game ends
            return over; 
        }
        
        printGrid(grid);			//print grid again

        if (CheckBoard(grid)) {			//check if grid is full
            printf("No more positions left!\nDOS%s wins!\n", DOS);
            over = 0; 				//game ends
            return over;  
        }
        
        do {			//DOS's turn
        	
        printf("DOS %s's turn. Choose the row number of position you want to remove (0-3): ", DOS);
        scanf("%d", &row);
        printf("DOS %s's turn. Choose the column number of position you want to remove (0-3): ", DOS);
        scanf("%d", &col);
        
	        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || strcmp(grid[row][col], EMPTY) == 0) {
	            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
	        		printf("Invalid move! Try again.\n");
				}
				else if (strcmp(grid[row][col], EMPTY) == 0) {
					printf("This position is already empty. Please choose another one\n");
				}
	        }
			 
        } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || strcmp(grid[row][col], EMPTY) == 0); 
        
        printf("DOS %s removes the move at position (%d, %d)\n", DOS, row, col);
    	strcpy(grid[row][col], EMPTY);		//remove DOS from the grid

    }
    
    return 0; 
}

int main() {
	int over;	// signals if game is over or not
    over = playGame();	//start game

	if (!over)
		printf("\nThank you for playing!");	// if game is over, will print thank you message
    return 0;
    
}
