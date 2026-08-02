# MAZE SOLVER
A C program that finds the shortest path through a text-based maze using the Breadth-First Search (BFS) algorithm. It includes an interactive menu, real-time terminal animations, and a benchmarking tool to measure algorithmic execution time.

## 📂 Project Structure
*   `main.c` - interactive menu and performance metrics.
*   `maze.c` & `maze.h` - File parsing, terminal animation, and BFS logic.
*   `stack.c` & `stack.h` - Custom LIFO Stack that stores position
*   `queue.c` & `queue.h` - Custom FIFO Queue that stores position
*   `position.h` - struct for row and column coordinates.

## 🚀 How to Compile and Run
This project requires a C compiler like GCC (MinGW on Windows).

**1. Compile the code:**

Open your terminal in the project folder and run:
```
gcc -Wall -std=c99 main.c maze.c stack.c queue.c -o maze_solver
```

**2. Run the program:**

* Windows: `.\maze_solver.exe`

* Linux/Mac: `./maze_solver`

## 📝 Maze File Format
The program reads mazes from standard `.txt` files. The first line must be the height and width, followed by the maze layout.

**Legend:**
* `S` - Start
* `G` - Goal
* `#` - Wall 
* `  ` (space) - Open path