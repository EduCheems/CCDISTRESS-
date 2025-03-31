#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define GRIDSIZE 4
#define UNO "('o')"
#define TRES "(-.-)"
#define EMPTY "     "

void initializeGrid(char grid[GRIDSIZE][GRIDSIZE][6]) {
	
	int i, j; 
	
    for (i = 0; i < GRIDSIZE; i++) {
        for (j = 0; j < GRIDSIZE; j++) {
        	strcpy(grid[i][j], EMPTY); 
        }
    }
}

void printGrid(char grid[GRIDSIZE][GRIDSIZE][6]) {
	
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

//How to add move: strcpy(grid[i][j], UNO) or strcpy(grid[i][j], TRES) Bale from an empty string we're gonna ovewrite it
//If dos, strcpy(grid[i][j], EMPTY) 

/* GAME STRUCTURE (VISUAL): 

    
    + --- + --- + --- + --- +    + --- + --- + --- + --- +    + --- + --- + --- + --- + 
    |     |     |     |     |    |(-.-)|     |('o')|('o')|    |(-.-)|     |('o')|('o')|
    + --- + --- + --- + --- +    + --- + --- + --- + --- +    + --- + --- + --- + --- + 
    |     |     |     |     |    |     |(-.-)|     |     |    |     |     |     |     |
    + --- + --- + --- + --- + -> + --- + --- + --- + --- + -> + --- + --- + --- + --- +
    |     |     |     |     |    |     |     |('o')|(-.-)|    |     |     |('o')|(-.-)| 
    + --- + --- + --- + --- +    + --- + --- + --- + --- +    + --- + --- + --- + --- + 
    |     |     |     |     |    |     |('o')|(-.-)|     |    |     |('o')|(-.-)|     | 
    + --- + --- + --- + --- +    + --- + --- + --- + --- +    + --- + --- + --- + --- + 

    UPDATE: *PLAYER* occupies (16) -> *DOS* removes (2,2) or *DOS* removes position no. 5 

    Applicable pa rin dito yung supposed logic ng code natin so far bale it's just that ang 
    way ng pag check lagi is via strcmp halimbawa para malaman mo kung nasa (2,2) na si *TRES*, 
    do if (strcmp(Grid[i][j], TRES) == 0) 

*/

int linearSearch(int arr[], int size, int key) {
    int i;
  
    for (i = 0; i < size; i++)
      if (key == arr[i])
        return i; // key found and will return index
  
    return -1; // key not found
  }
  
  void selectionSort(int player[], int size) {
    int i, j, min, temp;
  
    for (i = 0; i < size - 1; i++) {
      min = i; // min is the index of the lowest element
  
      for (j = i + 1; j < size; j++)
        if (player[j] < player[min])
          min = j;
  
      if (i != min) {
        temp = player[i];
        player[i] = player[min];
        player[min] = temp;
      }
    }
  }
  
  int isDosWin(int F[]) {
    int win = 0;
    int ctr = 0;
    int i;
  
    for (i = 0; i < 16; i++) {
      if (F[i] == 0)
        ctr++;
    }
  
    if (ctr == 16)
      win = 1;
  
    return win;
  }
  
  int isUnoTresWin(int player[], int W[][4]) {
    int found = 0;
    int win = 0;
    int ctr = 0;
    int set = 0;
    int i;
  
    // if player only has 4 positions, then there's a chance to win
    // if player has more than 4 positions, then automatically still not win
    if (player[4] == 0) {
      ctr = 0;
  
      while (ctr != 4 || set < 5) {
        for (i = 0; i < 4; i++) {
          found = linearSearch(player, 16, W[set][i]);
  
          if (found != -1)
            ctr++;
        }
  
        set++;
      }
    }
  
    // if satisfied the winning combination
    if (ctr == 4)
      win = 1;
  
    return win;
  }
  
  void errorMsg(int *pos) {
    while (*pos < 1 || *pos > 16) {
      printf("STOP! INVALID INPUT!\n");
      printf("Please only select a position from 1 to 16.\n");
      printf("Please select another position: ");
      scanf("%d", pos);
    }
  }
  
  void Dos(char name[], int F[], int Uno[], int Tres[]) {
    int pos; // position selected by a player
    int found = 0;
  
    printf("Player %s, please select a position: ", name);
    scanf("%d", &pos);
  
    errorMsg(&pos);
  
    found = linearSearch(F, 16, pos);
  
    while (found != -1) {
      printf("WHOOPS! This position hasn't been taken yet by either of the two "
             "players.\n");
      printf("Please select another position: ");
      scanf("%d", &pos);
  
      errorMsg(&pos);
  
      found = linearSearch(F, 16, pos);
    }
  
    found = linearSearch(Uno, 16, pos);
  
    if (found) {
      Uno[found] = 999;       // to place it at the back of the list
      selectionSort(Uno, 16); // sorts the list
      found = linearSearch(Uno, 16, 999);
      Uno[found] = 0; // takes the chosen position by Dos off Uno's list
  
    } else {
      found = linearSearch(Tres, 16, pos);
      Tres[found] = 999;       // to place it at the back of the list
      selectionSort(Tres, 16); // sorts the list
      found = linearSearch(Tres, 16, 999);
      Tres[found] = 0; // takes the chosen position by Dos off Tres's list
    }
  }
  
  void UnoTres(char name[], int F[], int player[]) {
    int pos; // position selected by a player
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
  
    F[found] = 0; // removes it from the available positions left
  
    // adding the position to the player's hand
    found = linearSearch(player, 16, 0); // finds the first empty position
    player[found] = pos;
  }
  
  void winningSets(int W[][4], int P[][4]) {
    int i, j;
  
    // Initialize First Set of Winning Set
    // {1, 2, 3, 4}
    for (i = 0; i < 4; i++)
      W[0][i] = P[0][i];
  
    // Initialize Second Set of Winning Set
    // {1, 6, 11, 16}
    for (i = 0; i < 4; i++)
      W[1][i] = P[i][i];
  
    // Initialize Third Set of Winning Set
    // {4, 7, 10, 13}
    j = 3; // from right to left diagonally
    for (i = 0; i < 4; i++) {
      W[2][i] = P[i][j];
      j--;
    }
  
    // Initialize Fourth Set of Winning Set
    // {13, 14, 15, 16}
    for (i = 0; i < 4; i++)
      W[3][i] = P[3][i];
  }
  
  void Grid(int P[][4]) {
    int x;
    int i, j;
  
    x = 1; // numbers 1-16 represent positions in the grid
           // 1 is at the uppermost left corner which is also the first position
           // in the grid 16 is at the lowermost right corner which is also the
           // last position in the grid
  
    // Initialize P
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        P[i][j] = x;
        x++;
      }
    }
  
    // Print Grid
  }
  
  int main() {
  
    int P[4][4]; // P is a 4x4 grid
    int F[16];   // F containins the available positions left in the grid
    char name[3]
             [5]; // name is a string array that contains the names of the players
    int W[4][4];  // W is the Winning Sets
    int Uno[16], Tres[16]; // players
    int turn = 1;          // signals whose turn it is
    int go = 0;            // signals whose turn it is
    int over = 0;          // signals if game is over
    int playerWin = 0;     // signals who won
                           // 1 for Uno, 2 for Dos, and 3 for Tres
    int i;
  
    // Initialize P
    Grid(P);
  
    // Initialize F
    for (i = 0; i < 16; i++)
      F[i] = i + 1;
  
    // Initialize names
    strcpy(name[0], "Uno");
    strcpy(name[1], "Dos");
    strcpy(name[2], "Tres");
  
    // Initialize W (winning sets)
    winningSets(W, P);
  
    while (!over) {
      if (turn == 1 && go == 1) {
        UnoTres("Uno", F, Uno);
        selectionSort(Uno, 16);
        over = isUnoTresWin(Uno, W);
  
        if (over)
          playerWin = 1;
        else {
          over = isDosWin(F);
  
          if (over)
            playerWin = 2;
          else {
            turn = !turn;
            go = !go;
          }
        }
  
      } else if (turn == 0) {
        Dos("Dos", F, Uno, Tres);
        turn = !turn;
  
      } else if (turn == 1 && go == 0) {
        UnoTres("Tres", F, Tres);
        selectionSort(Tres, 16);
        over = isUnoTresWin(Tres, W);
  
        if (over)
          playerWin = 3;
        else {
          over = isDosWin(F);
  
          if (over)
            playerWin = 2;
          else {
            turn = !turn;
            go = !go;
          }
        }
      }
    }
  
    if (playerWin == 1)
      printf("Congratulations, Player Uno! You won!");
    else if (playerWin == 2)
      printf("Congratulations, Player Dos! You won!");
    else if (playerWin == 3)
      printf("Congratulations, Player Tres! You won!");
  
    return 0;
  }
