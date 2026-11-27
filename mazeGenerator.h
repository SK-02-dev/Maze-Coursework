#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

enum Cell {
    WALL,
    EMPTY,
    EXIT,
    START
};

#define maxRows 41
#define maxCols 55

extern int mazeRows;
extern int mazeCols;
extern enum Cell maze[maxRows][maxCols];

extern int cellSize;
extern int startRow, startCol;
extern int exitRow, exitCol;

void setup(void);
void generateStartAndExit(void);
void generateSize(void);
void generateMaze(int row, int col);
void drawMaze(void);

#endif