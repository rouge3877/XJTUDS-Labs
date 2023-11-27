#include "Maze.h"

void printHelp()
{
    fprintf(stderr, "Usage: Maze <output_file> <start_position> <destination_position>\n");
    fprintf(stderr, "The position should be given in the form of [a,b].\n");
    fprintf(stderr, "The position should be in the range of the maze. And the range is ROE=%d, COL=%d\n", MAX_ROW, MAX_COL);
    fprintf(stderr, "Example: Maze output.txt [0,0] [9,6]\n");
    return;
}

char *getAbsolutePath(const char *filename)
{
    char buf[1024];
    getcwd(buf, sizeof(buf));
    char *path = (char *)malloc(1024 * sizeof(1024));
    strcpy(path, buf);
    strcat(path, "/");
    strcat(path, filename);
    return path;
}

int main(int argc, char *argv[])
{
    // 判断参数个数是否正确：除文件名外提供三个参数：输出文件、起点坐标、终点坐标，其中坐标以[a,b]形式给出
    int start_row;
    int start_col;
    int destination_row;
    int destination_col;
    FILE *output = NULL;
    if (argc != 3) {
        if (argc == 1) {
            output = stdout;
            fprintf(stdout, "Please input the start position and destination position in the form of [a,b].\n");
            fprintf(stdout, "The position should be in the range of the maze. And the range is ROE=0~%d, COL=0~%d\n", MAX_ROW, MAX_COL);
            fprintf(stdout, "Example: [0,0] [9,6]\n");
            scanf("[%d,%d] [%d,%d]", &start_row, &start_col, &destination_row, &destination_col);
        } else if (argc == 2 && strcmp(argv[1], "--help") == 0) {
            printfHelp();
            exit(0);
        } else {
            if (argc > 3)
                printf("Too many arguments.\n");
            else
                printf("Too few arguments.\n");
            printfHelp();
            exit(1);
        }
    } else {
        // 判断参数是否合法：起点坐标和终点坐标必须在迷宫范围内
        start_row = atoi(argv[1]);
        start_col = atoi(argv[2]);
        destination_row = atoi(argv[3]);
        destination_col = atoi(argv[4]);
        // 读入
        if (strcmp(argv[1], "stdout") == 0)
            output = stdout;
        else {
            char *output_path = getAbsolutePath(argv[1]);
            output = fopen(output_path, "w");
            if (!output) {
                fprintf(stderr, "Unable to open output file.\n");
                exit(1);
            }
            free(output_path);
        }
    }

    // 初始化迷宫
    pMaze maze = initMaze(MAX_ROW, MAX_COL);
    // 给定起点和终点
    Position start = {start_row, start_col};
    Position destination = {destination_row, destination_col};
    giveMazeStart(maze, &start);
    giveMazeDestination(maze, &destination);
    // 判断起点和终点是否合法
    if (!verifyStartAndDestination(maze)) {
        destoryMaze(maze);
        exit(1);
    }

    // 生成迷宫
    createMaze(maze, 0);
    printMaze(maze, output);
    // 找到迷宫路径
    findMazePath(maze, &start, &destination);
    printMazePath(maze, &start, &destination, output);

    // 释放迷宫
    destoryMaze(maze);
    fclose(output);

    return 0;
}
