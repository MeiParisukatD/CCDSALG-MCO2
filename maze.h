#ifndef MAZE_H
#define MAZE_H

#define _POSIX_C_SOURCE 199309L     // for nanosleep
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#include "stack.h"
#include "queue.h"

#define CLEARSCREEN "\033[H\033[J"  // escape sequence for clearing screen
#define DELAY 50                    // display delay in milliseconds 

// ANSI Escape Sequences
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[36m"
#define GREEN_BG "\033[42m"

// Maze struct declaration
typedef struct {
    char map[30][30];
    int height;      
    int width;       
    Position start;
    Position goal;
} Maze;

// Function Prototypes
void delay(long int milliseconds); 
Maze* loadMaze(char* filename);
void deleteMaze(Maze** mazePtr);
void displayMaze(Maze* maze);
void mazeBFS(Maze* maze, Position predecessor[30][30], int* cellsExplored, double* execTimeMs, int withAnimation);
Stack* buildPath(Maze* maze, Position predecessor[30][30]);
void animateSolution(Maze* maze, Stack* pathStack);

#endif // MAZE_H