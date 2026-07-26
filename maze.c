#include "maze.h"

void delay(long int milliseconds)
{
    struct timespec ts; 
    ts.tv_sec = milliseconds / 1000;                 
    ts.tv_nsec = (milliseconds % 1000) * 1000000;     

    nanosleep(&ts, NULL);
}

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

    // clear screen first before display
    printf(clearScreen);

    for (i = 0; i < maze->height; i++)
    {
        for (j = 0; j < maze->width; j++)
        {
            printf("%c", maze->map[i][j]);
        }
        printf("\n");
    }
}

void mazeBFS(Maze* maze, Position predecessor[30][30], int* cellsExplored)
{
    Queue* explore = createQueue();
    Position toExplore;
    Position up, right, down, left;
    int visited[30][30] = {0};
    int foundGoal = 0;
    *cellsExplored = 0;

    enqueue(explore, maze->start);
    visited[maze->start.row][maze->start.col] = 1;

    while(!isEmptyQueue(explore) && !foundGoal)
    {
        toExplore = dequeue(explore);
        (*cellsExplored)++;

        if (maze->map[toExplore.row][toExplore.col] != 'S' && maze->map[toExplore.row][toExplore.col] != 'G') 
        {
            maze->map[toExplore.row][toExplore.col] = '.'; 
        }
        
        displayMaze(maze); 
        delay(200);

        if (toExplore.row == maze->goal.row && toExplore.col == maze->goal.col)
        {
            foundGoal = 1;
        }
        else
        {
            up = right = down = left = toExplore;
            up.row--;
            right.col++;
            down.row++;
            left.col--;

            // up check
            if (up.row >= 0) 
            {
                if ((maze->map[up.row][up.col] == ' ' || maze->map[up.row][up.col] == 'G') && !visited[up.row][up.col])
                {
                    visited[up.row][up.col] = 1;
                    enqueue(explore, up);
                    predecessor[up.row][up.col] = toExplore;
                }
            }

            // down check
            if (down.row < maze->height) 
            {
                if ((maze->map[down.row][down.col] == ' ' || maze->map[down.row][down.col] == 'G') && !visited[down.row][down.col])
                {
                    visited[down.row][down.col] = 1;
                    enqueue(explore, down);
                    predecessor[down.row][down.col] = toExplore;
                }
            }

            // left check
            if (left.col >= 0) 
            {
                if ((maze->map[left.row][left.col] == ' ' || maze->map[left.row][left.col] == 'G') && !visited[left.row][left.col])
                {
                    visited[left.row][left.col] = 1;
                    enqueue(explore, left);
                    predecessor[left.row][left.col] = toExplore;
                }
            }

            // right check
            if (right.col < maze->width) 
            {
                if ((maze->map[right.row][right.col] == ' ' || maze->map[right.row][right.col] == 'G') && !visited[right.row][right.col])
                {
                    visited[right.row][right.col] = 1;
                    enqueue(explore, right);
                    predecessor[right.row][right.col] = toExplore;
                }
            }
        }
    }   

    deleteQueue(&explore);
}

Stack* determinePath(Maze* maze, Position predecessor[30][30]) 
{
    Stack* pathStack = createStack();
    Position step;
    
    // if the goal is not reached
    if (predecessor[maze->goal.row][maze->goal.col].row == -1) 
    {
        // return an empty stack
        return pathStack; 
    }

    step = maze->goal;

    // trace backward until start is reached
    while (step.row != -1 && step.col != -1) 
    {
        push(pathStack, step);
        step = predecessor[step.row][step.col]; 
    }
    
    return pathStack;
}

void animateSolution(Maze* maze, Stack* pathStack) 
{
    Position pos;

    if (pathStack == NULL || isEmptyStack(pathStack)) 
    {
        printf("\nNo valid path to animate!\n");
    } 
    else 
    {
        while (!isEmptyStack(pathStack)) 
        {
            pos = pop(pathStack);

            if (maze->map[pos.row][pos.col] != 'S' && maze->map[pos.row][pos.col] != 'G') 
                maze->map[pos.row][pos.col] = '*'; 

            displayMaze(maze); 
            delay(200);
        }
    }
}
