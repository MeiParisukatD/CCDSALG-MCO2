#ifndef MAZE_H
#define MAZE_H

#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#include "stacks.h"
#include "queue.h"

#define clearScreen "\033[H\033[J"

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
void mazeBFS(Maze* maze, Position predecessor[30][30], int* cellsExplored);

#endif // MAZE_H