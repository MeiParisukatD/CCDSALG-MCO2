#include "maze.h"

int main()
{
    int choice = 0;
    char filename[100];
    Maze* currentMaze = NULL;
    Position predecessor[30][30];
    Stack* path = NULL;
    
    int cellsExplored = 0;
    int pathLength = 0;
    int i, j;
    
    int iter;
    int totalIterations = 10000; 
    double tempTime, totalTime, execTime;   

    while (choice != 3)
    {
        printf("\n----------------------------------\n");
        printf("           MAZE SOLVER          \n");
        printf("----------------------------------\n");
        printf("1. Load Maze\n");
        printf("2. Start Simulation\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter filename (e.g., maze.txt): ");
                scanf("%s", filename);
                
                // frees the old maze first before loading a new one
                if (currentMaze != NULL)
                {
                    deleteMaze(&currentMaze);
                }
                
                // reading the maze map
                currentMaze = loadMaze(filename);
                
                if (currentMaze != NULL)
                {
                    printf("Maze successfully loaded!\n");
                }
                break;
            
            case 2:
                // if no maze map is loaded, display error message
                if (currentMaze == NULL)
                {
                    printf("Error: Please load a maze first before starting the simulation.\n");
                }
                else
                {
                    /* We gather execution time first before the animation */
                    tempTime = 0.0;
                    totalTime = 0.0;

                    // stress test the BFS algo to 10000 iterations to gather an execution time
                    for (iter = 0; iter < totalIterations; iter++)
                    {
                        // initialize the predecessor map positions to -1s
                        for (i = 0; i < 30; i++) {
                            for (j = 0; j < 30; j++) {
                                predecessor[i][j].row = -1;
                                predecessor[i][j].col = -1;
                            }
                        }
                        
                        // then run bfs without animation (a flag of 0)
                        mazeBFS(currentMaze, predecessor, &cellsExplored, &tempTime, 0); 
                        totalTime += tempTime;  // accumulate the time
                    }
                    
                    // average the total time by dividing it to the number of iterations
                    execTime = totalTime / totalIterations;
                    
                    /* Now we can run the single BFS with animation */
                    // initialize again the predecessor map since it has been populated by the previous BFS
                    for (i = 0; i < 30; i++)
                    {
                        for (j = 0; j < 30; j++)
                        {
                            predecessor[i][j].row = -1;
                            predecessor[i][j].col = -1;
                        }
                    }
                    
                    // run BFS with animation (a flag of 1)
                    mazeBFS(currentMaze, predecessor, &cellsExplored, &tempTime, 1);

                    // get the solution path
                    path = buildPath(currentMaze, predecessor);
                    
                    // get the size of the solution path (for the metrics)
                    if (path != NULL)
                    {
                        pathLength = path->size; 
                    }

                    // then display the animation of the solution path
                    animateSolution(currentMaze, path);

                    // lastly, display the metrics
                    printf("\n--- Simulation Metrics ---\n");
                    printf("Total cells explored : %d\n", cellsExplored);
                    printf("Final path length    : %d\n", pathLength);
                    printf("Execution time       : %.6f ms\n", execTime);

                    deleteStack(&path);
                    // delete the maze 
                    deleteMaze(&currentMaze);
                    printf("\n(Maze memory cleared. Please load the maze again to rerun.)\n");
                }
                break;
            
            case 3:
                printf("Exiting program. Goodbye!\n");
                if (currentMaze != NULL)
                {
                    deleteMaze(&currentMaze);
                }
                break;
            
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                break;
        }
    }
    
    return 0;
}