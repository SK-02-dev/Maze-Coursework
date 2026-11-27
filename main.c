#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graphics.h"
#include "mazeGenerator.h"
#include "solver.h"

int main()
{
    srand(time(NULL)); //ensures a random maze is generated each time
    
    setup(); //generates and displays maze (random dimensions and map each time)
    solveMaze(); //moves the robot through the maze
    return 0;
    
}






