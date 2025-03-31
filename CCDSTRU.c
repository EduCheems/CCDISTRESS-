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
