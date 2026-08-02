#include "maze.h"

void printBorder()
{
    printf(YELLOW "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" RESET);
}

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
        printf(YELLOW "\n-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+\n");
        printf("      ___  ___                  _____       _\n");              
        printf("      |  \\/  |                 /  ___|     | |\n");               
        printf("      | .  . | __ _ _______    \\ `--.  ___ | |_   _____ _ __\n"); 
        printf("      | |\\/| |/ _` |_  / _ \\    `--. \\/ _ \\| \\ \\ / / _ \\ '__|\n");
        printf("      | |  | | (_| |/ /  __/   /\\__/ / (_) | |\\ V /  __/ | \n");  
        printf("      \\_|  |_/\\__,_/___\\___|   \\____/ \\___/|_| \\_/ \\___|_|\n\n");  
        printf("                    USING BREADTH-FIRST SEARCH    \n"); 
        printf("-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+-+H+\n\n" RESET);
                                                       
        printf(CYAN "[1] Load Maze\n");
        printf("[2] Start Simulation\n");
        printf("[3] Exit\n\n" RESET);

        printBorder();
        
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
                    printBorder();
                    printf(GREEN "\nMaze successfully loaded!\n" RESET);
                }
                break;
            
            case 2:
                // if no maze map is loaded, display error message
                if (currentMaze == NULL)
                {
                    printBorder();
                    printf(RED "\nError: Please load a maze first before starting the simulation.\n" RESET);
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
                    if (path != NULL && path->size > 0)
                    {
                        pathLength = path->size - 1; // we need to subtract 1 to offset the Start node
                    }

                    // then display the animation of the solution path
                    animateSolution(currentMaze, path);

                    // lastly, display the metrics
                    printf("");
                    printf(YELLOW "\n-=-=-=-=- Simulation Metrics -=-=-=-=-\n" RESET);
                    printf("Total cells explored : %d\n", cellsExplored);
                    printf("Final path length    : %d\n", pathLength);
                    printf("Execution time       : %.6f ms\n", execTime);

                    deleteStack(&path);
                    // delete the maze 
                    deleteMaze(&currentMaze);
                    printf(CYAN "\n(Maze memory cleared. Please load the maze again to rerun.)\n" RESET);
                }
                break;
            
            case 3:
                printBorder();
                printf(CYAN "\nExiting program. Goodbye!\n" RESET);
                if (currentMaze != NULL)
                {
                    deleteMaze(&currentMaze);
                }
                break;
            
            default:
                printBorder();
                printf(RED "\nInvalid choice. Please enter 1, 2, or 3.\n" RESET);
                break;
        }
    }
    
    return 0;
}