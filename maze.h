#ifndef MAZE_H
#define MAZE_H

#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#include "stack.h"
#include "queue.h"

#define CLEARSCREEN "\033[H\033[J"
#define DELAY 50

// Maze struct declaration
typedef struct {
    char map[30][30];
    int height;      
    int width;       
    Position start;
    Position goal;
} Maze;

// Function prototypes
void delay(long int milliseconds); 
Maze* loadMaze(char* filename);
void deleteMaze(Maze** mazePtr);
void displayMaze(Maze* maze);
void mazeBFS(Maze* maze, Position predecessor[30][30], int* cellsExplored, double* execTimeMs, int withAnimation);
Stack* determinePath(Maze* maze, Position predecessor[30][30]);
void animateSolution(Maze* maze, Stack* pathStack);

#endif // MAZE_H