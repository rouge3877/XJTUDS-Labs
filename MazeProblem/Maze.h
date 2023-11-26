#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ROW 10
#define MAX_COL 7

#define EMPTY 'E'
#define WALL 'W'
#define PATH 'P'
#define VISITED 'V'
#define START 'S'
#define DESTINATION 'D'

typedef struct PosType {
    int _row;
    int _col;
} Position;

typedef struct Maze {
    char **_maze;
    Position _start;
    Position _destination;
    int _totalrow;
    int _totalcol;
} Maze, *pMaze;

pMaze initMaze(int, int);
void destoryMaze(pMaze);
void printMaze(pMaze, FILE *);
void giveMazeStart(pMaze, Position *);
void giveMazeDestination(pMaze, Position *);
bool verifyStartAndDestination(pMaze);
void createMaze(pMaze, int);
void findMazePath(pMaze, Position *, Position *);
void printMazePath(pMaze, Position *, Position *, FILE *);

#endif