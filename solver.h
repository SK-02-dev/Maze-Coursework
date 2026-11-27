#ifndef SOLVER_H
#define SOLVER_H

#include "mazeGenerator.h"

extern int robotRow, robotCol;
extern int robotDirection;

void drawRobot(void);
void forward(void);
void right(void);
void left(void);
int canMoveForward(int direction);
void solveMaze(void);

#endif