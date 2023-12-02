#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROW 3
#define MAX_COL 3

typedef struct Point {
    int _row, _col;
} Point;

typedef struct Wall {
    int _index1, _index2;
    bool _isWall;
} Wall;

Point index2point(int index, int row, int col)
{
    Point p;
    p._row = index / col;
    p._col = index % col;
    return p;
}

int point2index(Point p, int row, int col)
{
    return p._row * col + p._col;
}

int main(void)
{
    int Maze[MAX_ROW * MAX_COL];
    bool Wall[MAX_ROW * MAX_COL][MAX_ROW * MAX_COL];
    for (int i = 0; i < MAX_ROW * MAX_COL; i++) {
        Maze[i] = i;
        for (int j = 0; j < MAX_ROW * MAX_COL; j++) {
            Wall[i][j] = 0;
        }
    }

    // draw the maze
    for (int i = 0; i <= MAX_ROW; i++) {
        // draw the upper wall
        if (i == 0 || i == MAX_ROW) {
            for (int j = 0; j < MAX_COL; j++) {
                printf("+---");
            }
            printf("+\n");
        } else {
            for (int j = 0; j < MAX_COL; j++) {
                if (Wall[i * MAX_COL + j][i * MAX_COL + j - MAX_COL]) {
                    printf("+   ");
                } else {
                    printf("+---");
                }
            }
            printf("+\n");
        }

        // draw the left wall
        if (i != MAX_ROW) {
            for (int j = 0; j <= MAX_COL; j++) {
                if (j == 0) {
                    printf("|   ");
                } else if (Wall[i * MAX_COL + j][i * MAX_COL + j + 1]) {
                    printf("%d%d ", i * MAX_COL + j, i * MAX_COL + j + 1);
                } else if (Wall[i * MAX_COL + j][i * MAX_COL + j - 1] == 0) {
                    printf("|   ");
                } else if (j == MAX_COL) {
                    printf("|");
                }
            }
            printf("\n");
        }
    }
    return 0;
}