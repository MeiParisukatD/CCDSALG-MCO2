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
                
                if (currentMaze != NULL)
                {
                    deleteMaze(&currentMaze);
                }
                
                currentMaze = loadMaze(filename);
                
                if (currentMaze != NULL)
                {
                    printf("Maze successfully loaded!\n");
                }
                break;
            
            case 2:
                if (currentMaze == NULL)
                {
                    printf("Error: Please load a maze first before starting the simulation.\n");
                }
                else
                {
                    tempTime = 0.0;
                    totalTime = 0.0;

                    for (iter = 0; iter < totalIterations; iter++)
                    {
                        for (i = 0; i < 30; i++) {
                            for (j = 0; j < 30; j++) {
                                predecessor[i][j].row = -1;
                                predecessor[i][j].col = -1;
                            }
                        }
                        
                        mazeBFS(currentMaze, predecessor, &cellsExplored, &tempTime, 0); 
                        totalTime += tempTime;
                    }

                    execTime = totalTime / totalIterations;
                    
                    for (i = 0; i < 30; i++)
                    {
                        for (j = 0; j < 30; j++)
                        {
                            predecessor[i][j].row = -1;
                            predecessor[i][j].col = -1;
                        }
                    }

                    mazeBFS(currentMaze, predecessor, &cellsExplored, &tempTime, 1);

                    path = determinePath(currentMaze, predecessor);
                    
                    if (path != NULL)
                    {
                        pathLength = path->size; 
                    }

                    animateSolution(currentMaze, path);

                    printf("\n--- Simulation Metrics ---\n");
                    printf("Total cells explored : %d\n", cellsExplored);
                    printf("Final path length    : %d\n", pathLength);
                    printf("Execution time       : %.6f ms\n", execTime);

                    deleteStack(&path);
                    
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