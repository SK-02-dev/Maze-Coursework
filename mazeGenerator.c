#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mazeGenerator.h"
#include "solver.h"
#include "graphics.h"

int mazeRows;
int mazeCols;
enum Cell maze[maxRows][maxCols];
int mazeGenVisited[maxRows][maxCols];

int cellSize;
int startRow;
int startCol;
int exitRow;
int exitCol;



void setup() //initialises the maze and calls to procedures to generate its layout and draw the maze and the robot (in its starting position)
{
    generateSize(); //generates random maze dimensions and calculates cell size based on the dimensions 
    setWindowSize((40+(mazeCols*cellSize)), 900);

    //initialises every maze cell as a wall and marks all cells as unvisited for mazeGenerate()
    for (int i = 0; i<mazeRows; i++) 
    {
        for (int j = 0; j<mazeCols; j++)
        {
            maze[i][j] = WALL;
            mazeGenVisited[i][j] = 0; 
        }
    }

    generateStartAndExit(); //picks random coordinates for the start and exit of the maze (on different sides of the maze)
    generateMaze(1, 1); //generates the maze starting from [1,1], which is the first cell that isn't on the outer boundary reserved for the start and exit

    background();
    drawMaze();

    robotRow = startRow;
    robotCol = startCol;

    foreground();
    drawRobot(); //draws robot at the starting position

}

void generateSize() //generates random maze dimensions and calculates a suitable cell size based on the dimensions
{
    mazeRows = ((rand() % ((maxRows-9)/2))*2) + 11; 
    mazeCols = ((rand() % ((maxCols-9)/2))*2) + 11;

    cellSize = 40;

    int width = 1200 / mazeCols;
    int height = 550 / mazeRows;

    if (width<cellSize)
    {
        cellSize = width;
    }

    if (height<cellSize)
    {
        cellSize = height;
    }
}

void generateStartAndExit() //picks random coordinates for the start and exit of the maze (on different sides of the maze)
{
    int startSide = rand() % 4; //select a random side for the starting square, with 0 being the top row, 1 being the right column, 2 being the bottom row, and 3 being the left column
    int exitSide;
    do
    {
        exitSide = rand() % 4;
    } 
    while (exitSide==startSide); //makes sure the start and exit arent on the same side
    

    //generate random start and exit coordinates based on the sides generated
    if (startSide == 0)
    {
        startRow = 0;
        startCol = ((rand()%((mazeCols-2)/2))*2 + 1); 
    }
    if (startSide == 1)
    {
        startRow = ((rand()%((mazeRows-2)/2))*2 + 1);
        startCol = mazeCols-1;
    }
    if (startSide == 2)
    {
        startRow = mazeRows-1;
        startCol = ((rand()%((mazeCols-2)/2))*2 + 1);
    }
    if (startSide == 3)
    {
        startRow = ((rand()%((mazeRows-2)/2))*2 + 1);
        startCol = 0;
    }

    if (exitSide == 0)
    {
        exitRow = 0;
        exitCol = ((rand()%((mazeCols-2)/2))*2 + 1);
    }
    if (exitSide == 1)
    {
        exitRow = ((rand()%((mazeRows-2)/2))*2 + 1);
        exitCol = mazeCols-1;
    }
    if (exitSide == 2)
    {
        exitRow = mazeRows-1;
        exitCol = ((rand()%((mazeCols-2)/2))*2 + 1);
    }
    if (exitSide == 3)
    {
        exitRow = ((rand()%((mazeRows-2)/2))*2 + 1);
        exitCol = 0;
    }

   
    maze[startRow][startCol] = START;
    maze[exitRow][exitCol] = EXIT;

}

void generateMaze(int row, int col) //recursive; builds maze by randomly choosing paths through the grid. It creates paths by removing walls between cells that are two rows/columns apart.
{
    //mark the current cell as visited so it isnt visited again and make it empty so it forms part of the maze path
    mazeGenVisited[row][col] = 1;  
    maze[row][col] = EMPTY;

    //the four possible movement directions and the row and column changes to get from the current cell to a cell two columns or rows away
    int randDirection[4] = {0, 1, 2, 3};
    int rowChange[4] = {-2, 0, 2, 0};
    int colChange[4] = {0, 2, 0, -2};

    for (int i=0; i<4; i++)
    {
        int randomIndex = rand()%4; //shuffles the order of directions so the maze is generated in a random order
        int temp = randDirection[i];
        randDirection[i] = randDirection[randomIndex];
        randDirection[randomIndex] = temp;
    }

    //checks every direction to see if the cell two rows or columns away (depending on direction) can form part of the maze and carves a path towards it if it can
    for (int i=0; i<4; i++)
    {
        int direction = randDirection[i];
        int newRow = row + rowChange[direction];
        int newCol = col + colChange[direction];

        if (newRow >= 1 && newRow < mazeRows-1 && newCol >= 1 && newCol < mazeCols-1)
        {
            if (mazeGenVisited[newRow][newCol] == 0) //makes sure that the path is only cleared if the neighbouring cell hasnt been visited yet
            {
                int emptyRow = (row + newRow) / 2;
                int emptyCol = (col + newCol) / 2;
                maze[emptyRow][emptyCol] = EMPTY; //removes the wall between the two cells
                generateMaze(newRow,newCol);
            }
        }

        
    }
}

void drawMaze()
{
    //sets colours for the cells based on whether they are wall, empty, start, or exit
    for (int i=0; i<mazeRows; i++) 
    {
        for (int j=0; j<mazeCols; j++)
        {
            if (maze[i][j] == WALL)
            {
                setColour(darkgray);
            }
            else if (maze[i][j] == EMPTY)
            {
                setColour(white);
            }
            else if (maze[i][j] == START)
            {
                setColour(red);
            }
            else if (maze[i][j] == EXIT)
            {
                setColour(green);
  
            }
            fillRect((20+j*cellSize),(20+i*cellSize),cellSize,cellSize);
        }
    }


    //draws the internal maze grid lines
    setColour(black);
    for (int i=1; i<mazeRows; i++)
    {
        drawLine(20, (20+(i*cellSize)), (20+(mazeCols*cellSize)), (20+(i*cellSize)));
    }

    for (int j=1; j<mazeCols; j++)
    {
        drawLine(20+(j*cellSize), 20, (20+(j*cellSize)), (20+(mazeRows*cellSize)));
    }


    //draws the top and bottom outer walls but leaves gaps for the start and exit cells to create a visual difference
    for (int i=0; i < mazeRows; i++)
    {
        if (!((startCol == 0 && startRow == i) || (exitCol == 0 && exitRow == i)))
        {
            drawLine(20, 20+(i*cellSize), 20, 20+(i + 1)*cellSize);
        }

        if (!((startCol == mazeCols-1 && startRow == i) || (exitCol == mazeCols-1 && exitRow == i)))
        {
            drawLine((20+(mazeCols*cellSize)), (20+(i *cellSize)), (20+(mazeCols*cellSize)), (20+((i + 1)*cellSize)));
        }
    }

    //draws the left and right outer walls but leaves gaps for the start and exit cells to create a visual difference
    for (int j=0; j < mazeCols; j++)
    {
        if (!((startRow == 0 && startCol == j) || (exitRow == 0 && exitCol == j)))
        {
            drawLine((20+(j*cellSize)), 20, (20+((j + 1)*cellSize)), 20);
        }

        if (!((startRow == mazeRows-1 && startCol == j) || (exitRow == mazeRows-1 && exitCol == j)))
        {
            drawLine((20+(j*cellSize)), (20+(mazeRows*cellSize)), (20+((j+1)*cellSize)), (20+(mazeRows*cellSize)));
        }
    }
}