#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "mazeGenerator.h"
#include "graphics.h"


int robotCol;
int robotRow;
int robotDirection = 1; 
//0 = up, 1 = right, 2 = down, 3 = left



void forward() //moves the robot forward by one cell after checking that there is no wall in the way
{
    if (canMoveForward(robotDirection))
    {
        if (robotDirection == 0)
        {
            robotRow--;
        }
        else if (robotDirection == 1)
        {
            robotCol++;
        }
        else if (robotDirection == 2)
        {
            robotRow++;
        }
        else if (robotDirection == 3)
        {
            robotCol--;
        }

        foreground();
        clear();
        drawRobot(); //draws robot in its NEW position after moving forward
        sleep(150);
    }
     
}

void right() 
{
    robotDirection = (robotDirection+1)%4;
}

void left() 
{
    robotDirection = (robotDirection+3)%4;
}

void drawRobot() //draws the robot at its current position based on 'robotCol' and 'robotRow'. The robot is a pink circle with a black arrow in front of it to show the direction it is facing
{
    int x[3];
    int y[3];

    int robotX;
    int robotY;



    int radius = cellSize/3 + 1; //generates the robot's size based on the cell size
  
    if (radius<4)
    {
        radius = 4; //robot cannot have a radius smaller than 4 as then it would be too small to see properly
    }

    int halfbase = radius/2 + 4;
    int point = radius*2 - 4;
    int height = point-6;
    
    

    setColour(pink);
    robotX = 20 + (robotCol*cellSize) + cellSize/2;
    robotY = 20 + (robotRow*cellSize) + cellSize/2;
    fillOval(robotX-radius,robotY-radius,radius*2,radius*2);

    //sets dimensions of the direction arrow based on the size of the robot and draws it in black
    if (robotDirection == 0)
    {
        x[0] = robotX;
        y[0] = robotY - point;
        x[1] = robotX - halfbase;
        y[1] = robotY - height;
        x[2] = robotX + halfbase;
        y[2] = robotY - height;
    }
    else if (robotDirection == 1)
    {
        x[0] = robotX + point;
        y[0] = robotY;
        x[1] = robotX + height;
        y[1] = robotY - halfbase;
        x[2] = robotX + height;
        y[2] = robotY + halfbase;
    }
    else if (robotDirection == 2)
    {
        x[0] = robotX;
        y[0] = robotY + point;
        x[1] = robotX - halfbase;
        y[1] = robotY + height;
        x[2] = robotX + halfbase;
        y[2] = robotY + height;
    }
    else if (robotDirection == 3)
    {
        x[0] = robotX - point;
        y[0] = robotY;
        x[1] = robotX - height;
        y[1] = robotY - halfbase;
        x[2] = robotX - height;
        y[2] = robotY + halfbase;
    }

    setColour(black);
    fillPolygon(3, x, y);
    
}



int canMoveForward(int direction) //checks whether the cell in the provided direction directly in front of the robot is not a wall and can be moved into
{

    if (robotRow<0 || robotRow>=mazeRows ||robotCol<0 || robotCol>=mazeCols) //boundary check to ensure the robot is actually inside the maze
    {
        return 0;
    }
    else
    {
        if (robotCol>=0 && robotCol<(mazeCols-1) && direction == 1 && maze[robotRow][robotCol+1] != WALL)
        {
            return 1;
        }
        if (robotCol>0 && robotCol<=(mazeCols-1) && direction == 3 && maze[robotRow][robotCol-1] != WALL)
        {
            return 1;
        }
        if (robotRow>=0 && robotRow<(mazeRows-1) && direction == 2 && maze[robotRow+1][robotCol] != WALL)
        {
            return 1;
        }
        if (robotRow>0 && robotRow<=(mazeRows-1) && direction == 0 && maze[robotRow-1][robotCol] != WALL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }

}

int atMarker () //checks if robot has reached the exit cell
{
    if (maze[robotRow][robotCol] == EXIT)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void solveMaze() //navigates the robot through the maze using the wall hugging right hand rule until it finds the exit
{

    while (!atMarker())
    {
        right(); //always tries to turn right first and then checks the other directions if it cannot move right
        if(canMoveForward(robotDirection))
        {
            forward();
        }
        else
        {
            left();
            if(canMoveForward(robotDirection))
            {
                forward();
            }
            else
            {
                left();
                if(canMoveForward(robotDirection))
                {
                    forward();
                }
                else
                {
                    left();
                    if(canMoveForward(robotDirection))
                    {
                        forward();
                    }
                }
            }
        }
    }
    message("Maze completed!");

}