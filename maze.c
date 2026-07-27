#include "maze.h"

/*
    Purpose: Pauses program for a given duration using nanosleep
    @param : milliseconds is the duration to pause execution
    Precondition: milliseconds must be a positive integer
*/
void delay(long int milliseconds)
{
    struct timespec ts; 
    ts.tv_sec = milliseconds / 1000;                 
    ts.tv_nsec = (milliseconds % 1000) * 1000000;     

    nanosleep(&ts, NULL);
}

/*
    Purpose: Reads a maze map from a given text file and initializes the Maze structure
    Returns: Either
             a) a pointer to the newly allocated Maze
             b) NULL if the file could not be opened
    @param : filename is the string name of the maze text file
    Precondition: If the text file exists, it must follow the exact "height width then map" format.
*/
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
            // initialize the start and goal position to {-1,-1}
            maze->start.row = -1;
            maze->start.col = -1;
            maze->goal.row = -1;
            maze->goal.col = -1;

            // read the height and width
            fscanf(fp, "%d %d", &maze->height, &maze->width);

            // skip to the next line
            fscanf(fp, "%*[^\n]");
            fscanf(fp, "%*c");

            // reading the map char by char
            for (i = 0; i < maze->height; i++)
            {
                for (j = 0; j < maze->width; j++)
                {
                    fscanf(fp, "%c", &maze->map[i][j]);

                    if (maze->map[i][j] == 'S') // if the read char is 'S', assign its position
                    {
                        maze->start.row = i;
                        maze->start.col = j;
                    }
                    else if (maze->map[i][j] == 'G') // if the read char is 'G', assign its position
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
    else    // display an error message if file does not exist or inaccessible
    {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
    }

    return maze;
}

/*
    Purpose: Deallocates memory associated with the Maze struct
    @param : mazePtr is a double pointer to the maze so it can be safely set to NULL after deletion.
    Precondition: mazePtr must point to a dynamically allocated Maze
*/
void deleteMaze(Maze** mazePtr)
{
    if (mazePtr != NULL && *mazePtr != NULL)
    {
        free(*mazePtr);
        *mazePtr = NULL;
    }
}

/*
    Purpose: Clears the terminal then displays the current state of the maze map
    @param : maze is a pointer to the Maze struct
    Precondition: maze must be successfully loaded and initialized
*/
void displayMaze(Maze* maze)
{
    int i, j;

    // clear screen first before display
    printf(CLEARSCREEN);

    for (i = 0; i < maze->height; i++)
    {
        for (j = 0; j < maze->width; j++)
        {
            printf("%c", maze->map[i][j]);
        }
        printf("\n");
    }
}

/*
    Purpose: Executes the Breadth-First Search (BFS) algorithm to find the shortest path.
             Also tracks its execution time
    @param : maze is a pointer to the Maze struct
    @param : predecessor is a 2D array used to track the path history for backtracking
    @param : cellsExplored tracks the total number of cells visited
    @param : execTimeMs accumulates the execution time in milliseconds
    @param : withAnimation is a flag (1 to animate search, 0 for benchmarking)
    Precondition: predecessor array must be initialized to -1 before calling
*/
void mazeBFS(Maze* maze, Position predecessor[30][30], int* cellsExplored, double* execTimeMs, int withAnimation)
{
    Queue* explore = createQueue();
    Position toExplore;
    Position up, right, down, left;
    int visited[30][30] = {0};
    int foundGoal = 0;
    clock_t start_tick, end_tick;
    
    *cellsExplored = 0;
    *execTimeMs = 0.0;

    start_tick = clock(); // start time

    enqueue(explore, maze->start);
    visited[maze->start.row][maze->start.col] = 1;

    end_tick = clock(); // pause

    // add the time got
    *execTimeMs += ((double)(end_tick - start_tick)) / CLOCKS_PER_SEC * 1000.0; 

    while(!isEmptyQueue(explore) && !foundGoal)
    {
        start_tick = clock(); // resume time again

        toExplore = dequeue(explore);
        (*cellsExplored)++;

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

        end_tick = clock(); // pause time 

        // add the time got again
        *execTimeMs += ((double)(end_tick - start_tick)) / CLOCKS_PER_SEC * 1000.0;

        // displaying of maze will only be executed if the flag withAnimation is 1
        if (!foundGoal && withAnimation)
        {
            if (maze->map[toExplore.row][toExplore.col] != 'S' && maze->map[toExplore.row][toExplore.col] != 'G') 
            {
                maze->map[toExplore.row][toExplore.col] = '.'; 
            }
            displayMaze(maze); 
            delay(DELAY);
        }
    }   

    deleteQueue(&explore);
}

/*
    Purpose: Backtracks from the Goal to the Start using the predecessor map to create the sequence of 
             solution path. The path sequence will be stored in a Stack.
    Returns: a Stack containing the path sequence from (Goal -> Start), else empty Stack is returned if 
             the predecessor of the goal is -1 (meaning it was not reached)
    @param : maze is a pointer to the Maze struct.
    @param : predecessor is the 2D map tracing the parent of every visited node.
    Precondition: mazeBFS must have been run to populate the predecessor array
*/
Stack* buildPath(Maze* maze, Position predecessor[30][30]) 
{
    Stack* pathStack = createStack();
    Position step;
    
    // if the Goal is not reached
    if (predecessor[maze->goal.row][maze->goal.col].row == -1) 
    {
        // return an empty stack
        return pathStack; 
    }

    step = maze->goal;

    // trace backward until Start is reached
    while (step.row != -1 && step.col != -1) 
    {
        push(pathStack, step);
        step = predecessor[step.row][step.col]; 
    }
    
    return pathStack;
}

/*
    Purpose: Draws the final solution path by popping positions from the stack
    @param : maze is a pointer to the Maze struct
    @param : pathStack is a pointer to the Stack containing the backward path sequence
*/
void animateSolution(Maze* maze, Stack* pathStack) 
{
    Position pos;

    // if the pathStack is null or empty, that means that there is no solution
    if (pathStack == NULL || isEmptyStack(pathStack)) 
    {
        printf("\nNo valid path!\n");
    } 
    else 
    {
        while (!isEmptyStack(pathStack)) 
        {
            pos = pop(pathStack);

            if (maze->map[pos.row][pos.col] != 'S' && maze->map[pos.row][pos.col] != 'G') 
                maze->map[pos.row][pos.col] = '*'; 

            displayMaze(maze); 
            delay(DELAY);
        }
    }
}
