Maze Coursework
This program generates a maze with random dimensions (between 11x11 and 33x55) and a random path.
The maze has a one cell thick outer border with one start cell and one exit cell. The empty path cells are all within this border.
The maze is displayed in a drawapp window, and the program also animates a robot navigating through the maze using the wall hugging right hand rule.

FILES
The program is divided into three main files:
    main.c, mazeGenerator.c and solver.c.

    main.c seeds the random number generator which is used throughout the program, and it also calls to setup() in order to initialise, generate, and display the maze. It then calls to solveMaze() to display the robot moving through the maze.

    mazeGenerator.c handles maze generation:
        The maze is represented as a 2D array of enum Cell values, which can either be a wall, an empty space, a start cell, or an exit cell.
        The maze dimensions are randomly selected (although the rows and columns are always odd).
        The start and exit positions are also randomly generated.
        The maze path itself is generated using a recursive algorithm which starts at [1,1]. 
        The algorithm removes the walls between cells and unvisited neighbouring cells to create the path and continues until all reachable cells have been explored. 

    solver.c handles displaying the robot and actually moving it through the maze:
        The robot is represented by a pink circle with a black arrow in front of it, pointing in the direction the robot is currently facing.
        The robot can only move forward if the space in front is empty, a start cell, or an exit cell. Each time it moves, it is redrawn to visually show updates as it traverses the maze.
        The maze is navigated using the wall hugging right hand rule. The robot always attempts to turn right first, and if it cannot, it attempts to move forwards. If it cannot, it attempts to move to the left, and if it still cannot, it moves backwards. 
        This process repeats till the robot finds the exit cell.

COMMANDS TO COMPILE AND RUN THE PROGRAM
Compilation
clang main.c mazeGenerator.c solver.c graphics.c -o maze
Execution
./maze | java -jar drawapp-5.0.jar