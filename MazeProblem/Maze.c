#include "Maze.h"

pMaze initMaze(int total_row, int total_col)
{
    pMaze maze = (pMaze)malloc(sizeof(Maze));
    maze->_start._row = -1;
    maze->_start._col = -1;
    maze->_destination._row = -1;
    maze->_destination._col = -1;
    maze->_totalrow = total_row;
    maze->_totalcol = total_col;

    maze->_maze = (char **)malloc(total_row * sizeof(char *));
    for (int i = 0; i < total_row; i++) {
        maze->_maze[i] = (char *)malloc(total_col * sizeof(char));
        for (int j = 0; j < total_col; j++) {
            maze->_maze[i][j] = EMPTY;
        }
    }
    // 迷宫的四周设置为墙
    for (int i = 0; i < total_row; i++) {
        maze->_maze[i][0] = WALL;
        maze->_maze[i][total_col - 1] = WALL;
    }
    for (int i = 0; i < total_col; i++) {
        maze->_maze[0][i] = WALL;
        maze->_maze[total_row - 1][i] = WALL;
    }

    return maze;
}

void destoryMaze(pMaze maze)
{
    for (int i = 0; i < maze->_totalrow; i++) {
        free(maze->_maze[i]);
    }
    free(maze->_maze);
    free(maze);
}

//绘制迷宫，#表示墙，出入口用@表示，路径用*表示，同时在图的左方和上方加上行和列的数字编号（从1开始）
void printMaze(pMaze maze, FILE *output){
    fprintf(output, " ");
    for (int i = 0; i < maze->_totalcol; i++) {
        fprintf(output, "%d", i + 1);
    }
    fprintf(output, "\n");
    for (int i = 0; i < maze->_totalrow; i++) {
        fprintf(output, "%d", i + 1);
        for (int j = 0; j < maze->_totalcol; j++) {
            fprintf(output, "%c", maze->_maze[i][j]);
        }
        fprintf(output, "\n");
    }
    return;
}

void giveMazeStart(pMaze maze, Position *start)
{
    maze->_start._row = start->_row;
    maze->_start._col = start->_col;
    maze->_maze[start->_row][start->_col] = START;
    return;
}

void giveMazeDestination(pMaze maze, Position *destination)
{
    maze->_destination._row = destination->_row;
    maze->_destination._col = destination->_col;
    maze->_maze[destination->_row][destination->_col] = DESTINATION;
    return;
}

bool verifyStartAndDestination(pMaze maze)
{
    // 判断是否有起终点
    if (maze->_start._row == -1 || maze->_start._col == -1) {
        fprintf(stderr, "Start position is not given.\n");
        return false;
    }
    if (maze->_destination._row == -1 || maze->_destination._col == -1) {
        fprintf(stderr, "Destination position is not given.\n");
        return false;
    }
    // 判断起终点是否在迷宫范围内
    if (maze->_start._row < 0 || maze->_start._row >= maze->_totalrow || maze->_start._col < 0 || maze->_start._col >= maze->_totalcol) {
        fprintf(stderr, "Start position is out of range.\n");
        return false;
    }
    if (maze->_destination._row < 0 || maze->_destination._row >= maze->_totalrow || maze->_destination._col < 0 || maze->_destination._col >= maze->_totalcol) {
        fprintf(stderr, "Destination position is out of range.\n");
        return false;
    }
    // 判断起终点是否在同一位置
    if (maze->_start._row == maze->_destination._row && maze->_start._col == maze->_destination._col) {
        fprintf(stderr, "Start position and destination position are the same.\n");
        return false;
    }
    // 判断起点是否不在迷宫外周
    if (!(maze->_start._row == 0 || maze->_start._row == maze->_totalrow - 1 || maze->_start._col == 0 || maze->_start._col == maze->_totalcol - 1)) {
        fprintf(stderr, "Start position is not on the edge of the maze.\n");
        return false;
    }
    return true;
}

void createMaze(pMaze maze, int seed) // 使用prim算法生成迷宫
{
    
}

void findMazePath(pMaze maze, Position *start, Position *destination)