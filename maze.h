#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct {
    char** map;
    int height;      
    int width;       
    Position start;
    Position goal;
} Maze;

Maze* loadMaze(char* filename) 
{

}

void freeMaze(Maze** mazePtr)
{
    
}