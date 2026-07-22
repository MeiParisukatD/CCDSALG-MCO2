#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct {
    char map[30][30];
    int height;      
    int width;       
    Position start;
    Position goal;
} Maze;

Maze* loadMaze(char* filename) 
{
    Maze* maze = NULL;
    FILE* fp;
    int i, j;

    fp = fopen(filename, "r");

    if (fp != NULL)
    {
        maze = (Maze*)malloc(sizeof(Maze));
        
        if (maze != NULL)
        {
            maze->start.row = -1;
            maze->start.col = -1;
            maze->goal.row = -1;
            maze->goal.col = -1;

            fscanf(fp, "%d %d", &maze->height, &maze->width);

            // skip to the next line
            fscanf(fp, "%*[^\n]");
            fscanf(fp, "%*c");

            for (i = 0; i < maze->height; i++)
            {
                for (j = 0; j < maze->width; j++)
                {
                    fscanf(fp, "%c", &maze->map[i][j]);

                    if (maze->map[i][j] == 'S')
                    {
                        maze->start.row = i;
                        maze->start.col = j;
                    }
                    else if (maze->map[i][j] == 'G')
                    {
                        maze->goal.row = i;
                        maze->goal.col = j;
                    }
                }

                // skip to the next line
                fscanf(fp, "%*[^\n]");
                fscanf(fp, "%*c");
            }

        }
        fclose(fp);
    }
    else
    {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
    }

    return maze;
}

void deleteMaze(Maze** mazePtr)
{
    if (mazePtr != NULL && *mazePtr != NULL)
    {
        free(*mazePtr);
        *mazePtr = NULL;
    }
}

void displayMaze(Maze* maze)
{
    int i, j;

    for (i = 0; i < maze->height; i++)
    {
        for (j = 0; j < maze->width; j++)
        {
            printf("%c", maze->map[i][j]);
        }
        printf("\n");
    }
}
