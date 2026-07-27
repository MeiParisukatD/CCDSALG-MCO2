#include "maze.c"

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
    
    clock_t start_time, end_time;
    double exec_time_ms;

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
                    for (i = 0; i < 30; i++)
                    {
                        for (j = 0; j < 30; j++)
                        {
                            predecessor[i][j].row = -1;
                            predecessor[i][j].col = -1;
                        }
                    }

                    start_time = clock();
                    
                    mazeBFS(currentMaze, predecessor, &cellsExplored);
                    
                    end_time = clock();
                    
                    exec_time_ms = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;

                    path = determinePath(currentMaze, predecessor);
                    
                    if (path != NULL)
                    {
                        pathLength = path->size; 
                    }

                    animateSolution(currentMaze, path);

                    printf("\n--- Simulation Metrics ---\n");
                    printf("Total cells explored : %d\n", cellsExplored);
                    printf("Final path length    : %d\n", pathLength);
                    printf("Execution time       : %.2f ms\n", exec_time_ms);

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