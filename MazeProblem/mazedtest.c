#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_ROW 10
#define MAX_COL 10

#define MAX_QUEUE_SIZE 100

#define MAZE_PATH 0
#define MAZE_WALL 1
#define MAZE_VISITED 2

#define GRAPH_EXIST_EDGE 1
#define GRAPH_NO_EDGE 0

typedef struct Edge {
    int _row;
    int _col;
} Edge, *pEdge;

typedef struct Point {
    int _x;
    int _y;
} Point, *pPoint;

typedef struct Graph {
    int _edgeNum;
    int _vertexNum;
    int **_adjMatrix;
    pPoint *_vertexs;
} Graph, *pGraph;

typedef struct Maze {
    int _row;
    int _col;
    pGraph _graph;
} Maze, *pMaze;

typedef struct Queue {
    int _front;
    int _rear;
    int _size;
    int _capacity;
    int *_data;
} Queue, *pQueue;

pGraph createGraph(int vertexNum)
{
    pGraph graph = (pGraph)malloc(sizeof(Graph));
    graph->_edgeNum = 0;
    graph->_vertexNum = vertexNum;
    graph->_adjMatrix = (int **)malloc(sizeof(int *) * vertexNum);
    graph->_vertexs = (pPoint *)malloc(sizeof(pPoint) * vertexNum);
    for (int i = 0; i < vertexNum; i++) {
        graph->_adjMatrix[i] = (int *)malloc(sizeof(int) * vertexNum);
        graph->_vertexs[i] = (pPoint)malloc(sizeof(Point));
        graph->_vertexs[i]->_x = i / 10;
        graph->_vertexs[i]->_y = i % 10;
        for (int j = 0; j < vertexNum; j++) {
            graph->_adjMatrix[i][j] = 0;
        }
    }
    return graph;
}

void printGraph(pGraph graph)
{
    int vertexNum = graph->_vertexNum;
    int **adjMatrix = graph->_adjMatrix;
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void addEdge(pGraph graph, pEdge edge)
{
    int row = edge->_row;
    int col = edge->_col;
    graph->_adjMatrix[row][col] = GRAPH_EXIST_EDGE;
    graph->_adjMatrix[col][row] = GRAPH_EXIST_EDGE;
    graph->_edgeNum++;
}

void removeEdge(pGraph graph, pEdge edge)
{
    int row = edge->_row;
    int col = edge->_col;
    graph->_adjMatrix[row][col] = GRAPH_NO_EDGE;
    graph->_adjMatrix[col][row] = GRAPH_NO_EDGE;
    graph->_edgeNum--;
}

// 初始化迷宫
pMaze initMaze(int row, int col)
{
    pMaze maze = (pMaze)malloc(sizeof(Maze));
    maze->_row = row;
    maze->_col = col;
    maze->_graph = createGraph(row * col);
    return maze;
}

// 打印迷宫，注意边界
void printMaze(pMaze maze, FILE *fp)
{
    int row = maze->_row;
    int col = maze->_col;
    int **adjMatrix = maze->_graph->_adjMatrix;

    for (int i = 0; i < row; i++) {
        fprintf(fp, "+");
        for (int j = 0; j < col; j++) {
            fprintf(fp, "---+");
        }
        fprintf(fp, "\n");

        fprintf(fp, "|");
        for (int j = 0; j < col; j++) {
            // 检查当前位置和右侧位置之间是否有边
            if (j < col - 1 && adjMatrix[i * col + j][i * col + j + 1] == GRAPH_NO_EDGE) {
                fprintf(fp, "   |");
            } else {
                fprintf(fp, "   ");
            }
        }
        fprintf(fp, "|");
        fprintf(fp, "\n");
    }

    fprintf(fp, "+");
    for (int j = 0; j < col; j++) {
        fprintf(fp, "---+");
    }
    fprintf(fp, "\n");
}

// 图的Kruskal算法，最小生成树
void kruskal(pGraph graph){
    
}


// 测试迷宫的生成和打印（Kruskal算法）
int main()
{
    srand(time(NULL));
    pMaze maze = initMaze(MAX_ROW, MAX_COL);
    createMazeInKruskal(maze);
    printGraph(maze->_graph);
    printMaze(maze, stdout);
    return 0;
}