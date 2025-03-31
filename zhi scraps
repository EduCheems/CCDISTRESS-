#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define GRIDSIZE 4
#define UNO "('o')"
#define TRES "(-.-)"
#define EMPTY "     "

char grid[GRIDSIZE][GRIDSIZE][6];
int available_positions[16];
int Uno[16], Tres[16], Dos[16];

void initializeGrid() {
	int i, j; 
	
    	for (i = 0; i < GRIDSIZE; i++) {
        	for (j = 0; j < GRIDSIZE; j++) {
        		strcpy(grid[i][j], EMPTY); 
        }
    }
	for (i = 0; i < 16; i++){
		available_positions[i] = i + 1;
	}

	memset(Uno, 0, sizeof(Uno));
    	memset(Tres, 0, sizeof(Tres));
    	memset(Dos, 0, sizeof(Dos));
}

void printGrid() {
	int i, j; 
	
    	for (i = 0; i < GRIDSIZE; i++) {
        	printf("+ --- + --- + --- + --- +\n");
        	for (j = 0; j < GRIDSIZE; j++) {
            		printf("|%s", grid[i][j]);
        	}
        printf("|\n");
    }
    printf("+ --- + --- + --- + --- +\n");
}

int linearSearch(int arr[], int size, int key) {
	int i;
   	
	for (i = 0; i < size; i++) {
        	if (arr[i] == key) {
            		return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

// Selection sort function to sort the player's positions array
void selectionSort(int player[], int size) {
	int i, j, min, temp;
    	for (i = 0; i < size - 1; i++) {
        	min = i;
        	for (j = i + 1; j < size; j++) {
            		if (player[j] < player[min]) {
                		min = j;
            		}
        	}
        	if (i != min) {
            		temp = player[i];
            		player[i] = player[min];
            		player[min] = temp;
        	}
    	}
}
  
// Error message for invalid position
void errorMsg(int *pos) {
	while (*pos < 1 || *pos > 16) {
        	printf("STOP! INVALID INPUT!\n");
        	printf("Please only select a position from 1 to 16.\n");
        	printf("Please select another position: ");
        	scanf("%d", pos);
    	}
}

// Dos's action (remove a position from Uno or Tres)
void Dos(char name[], int F[], int Uno[], int Tres[]) {
	int pos;
    	int found = 0;
    
    	printf("Player %s, please select a position to remove: ", name);
    	scanf("%d", &pos);
    
    	errorMsg(&pos);
    
    	found = linearSearch(F, 16, pos);
    
    	while (found != -1) {
        	printf("WHOOPS! This position hasn't been taken yet by either of the two players.\n");
        	printf("Please select another position: ");
        	scanf("%d", &pos);
        
        	errorMsg(&pos);
        
        	found = linearSearch(F, 16, pos);
    	}
    
    // Remove position from Uno or Tres
    	found = linearSearch(Uno, 16, pos);
    	if (found != -1) {
        	Uno[found] = 999;  // Mark as removed
        	selectionSort(Uno, 16);
        	Uno[linearSearch(Uno, 16, 999)] = 0;  // Remove from Uno
    	} else {
        	found = linearSearch(Tres, 16, pos);
        	Tres[found] = 999;  // Mark as removed
        	selectionSort(Tres, 16);
        	Tres[linearSearch(Tres, 16, 999)] = 0;  // Remove from Tres
    	}
}

// Uno or Tres's move (select a position)
void UnoTres(char name[], int F[], int player[]) {
	int pos;
    	int found = 0;
    
    	printf("Player %s, please select a position: ", name);
    	scanf("%d", &pos);
    
    	errorMsg(&pos);
    
    	found = linearSearch(F, 16, pos);
    
    	while (found == -1) {
        	printf("OH NO! This position has already been taken!\n");
        	printf("Please select another position: ");
        	scanf("%d", &pos);
        
        	errorMsg(&pos);
        
        	found = linearSearch(F, 16, pos);
    	}
    
    	F[found] = 0;  // Remove from available positions
    
    	// Add position to the player's list
    	found = linearSearch(player, 16, 0);  // Find first empty slot
    	player[found] = pos;
}

// Check if Dos has won (all positions taken)
int isDosWin() {
	for (int i = 0; i < 16; i++) {
        	if (Dos[i] == 0) return 0;  // If any position is empty, Dos hasn't won yet
    	}
    	return 1;  // All positions taken
}

// Check if Uno or Tres has won (check their positions for any winning set)
int isPlayerWin(int player[], int W[][4]) {
	for (int i = 0; i < 4; i++) {
		int ctr = 0;
        	for (int j = 0; j < 4; j++) {
            		if (linearSearch(player, 16, W[i][j]) != -1) {
                		ctr++;
            		}
        	}
        	if (ctr == 4) return 1;  // Winning combination found
    	}
    return 0;
}

// Define the winning sets (this is specific to the 4x4 grid)
void winningSets(int W[][4], int P[][4]) {
	int i, j;
    
    	// Initialize First Set of Winning Set {1, 2, 3, 4}
    	for (i = 0; i < 4; i++) W[0][i] = P[0][i];
    
    	// Initialize Second Set of Winning Set {1, 6, 11, 16}
    	for (i = 0; i < 4; i++) W[1][i] = P[i][i];
    
    	// Initialize Third Set of Winning Set {4, 7, 10, 13}
    	j = 3;
    	for (i = 0; i < 4; i++) {
		W[2][i] = P[i][j];
        	j--;
    	}
    
    	// Initialize Fourth Set of Winning Set {13, 14, 15, 16}
    	for (i = 0; i < 4; i++) W[3][i] = P[3][i];
}

void Grid(int P[][4]) {
	int x = 1;
    	for (int i = 0; i < 4; i++) {
        	for (int j = 0; j < 4; j++) {
            		P[i][j] = x++;
        	}
    	}
    	printGrid();
}

int main() {
	int P[4][4];  // Grid positions
    	int F[16];    // Available positions
    	char name[3][5];  // Player names
    	int W[4][4];  // Winning sets
    	int pos;      // Selected position
    	int turn = 1; // Whose turn it is (1 = Uno, 2 = Tres)
    	int over = 0; // Game over flag
    	int playerWin = 0; // Who won (1 = Uno, 2 = Tres, 3 = Dos)
    
    	// Initialize the game
    	initializeGrid();
    	Grid(P);
    
    	// Set up available positions
    	for (int i = 0; i < 16; i++) F[i] = i + 1;
    
    	// Player names
    	strcpy(name[0], "Uno");
    	strcpy(name[1], "Dos");
    	strcpy(name[2], "Tres");
    
    	// Define the winning sets
    	winningSets(W, P);
    
    	// Main game loop
    	while (!over) {
        	if (turn == 1) { // Uno's turn
            		UnoTres("Uno", F, Uno);
            		selectionSort(Uno, 16);
            		over = isPlayerWin(Uno, W);
            		if (over) playerWin = 1;
        	} else if (turn == 2) { // Tres's turn
            		UnoTres("Tres", F, Tres);
            		selectionSort(Tres, 16);
            		over = isPlayerWin(Tres, W);
            		if (over) playerWin = 2;
        	} else if (turn == 3) { // Dos's turn
			Dos("Dos", F, Uno, Tres);
            		turn = 1; // Switch back to Uno
        	}
        
        	if (over) {
            		printf("Congratulations, Player %s! You won!\n", name[playerWin - 1]);
        	} else {
           		turn = (turn % 3) + 1; // Switch turn to the next player
        	}
    	}
    
    return 0;
}








