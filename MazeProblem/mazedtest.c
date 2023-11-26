#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 9
#define N 9
#define WALL 0
#define SPACE 1
#define FRONTIER 3

#define OFFSET_COUNT 4
int offsets[OFFSET_COUNT][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}};

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point *data;
    int size;
    int capacity;
} PointVector;

void init_vector(PointVector *v)
{
    v->size = 0;
    v->capacity = 10;
    v->data = (Point *)malloc(sizeof(Point) * v->capacity);
}

void push_back(PointVector *v, int x, int y)
{
    // 扩容
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->data = (Point *)realloc(v->data, sizeof(Point) * v->capacity);
    }
    // 添加元素
    v->data[v->size].x = x;
    v->data[v->size].y = y;
    v->size++;
}

void erase(PointVector *v, int index)
{
    // 移动元素
    for (int i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}

int maze[M][N];

void generate_maze()
{
    // 初始化墙和矩阵
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            maze[i][j] = WALL;
        }
    }

    // 将初始点添加到空地中，并将初始点的邻居添加到frontiers中
    PointVector frontiers;
    init_vector(&frontiers);
    int x = 1;
    int y = 1;
    maze[x][y] = SPACE;
    for (int i = 0; i < OFFSET_COUNT; i++) {
        int nx = x + offsets[i][0] * 2;
        int ny = y + offsets[i][1] * 2;
        if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
            maze[nx][ny] = FRONTIER;
            push_back(&frontiers, nx, ny);
        }
    }

    // 随机种子
    srand((unsigned)time(NULL));

    // 当frontiers不为空时，取一个随机点
    while (frontiers.size > 0) {
        int r = rand() % frontiers.size;
        x = frontiers.data[r].x, y = frontiers.data[r].y;
        erase(&frontiers, r);

        maze[x][y] = SPACE;

        for (int i = 0; i < OFFSET_COUNT; i++) {
            int nx = x + offsets[i][0] * 2;
            int ny = y + offsets[i][1] * 2;
            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                if (maze[nx][ny] == WALL) {
                    maze[nx - offsets[i][0]][ny - offsets[i][1]] = SPACE; // 后一步操作
                    maze[nx][ny] = FRONTIER;
                    push_back(&frontiers, nx, ny);
                }
            }
        }
    }
}

void print_maze()
{
    int i, j;
    for (i = 0; i < M + 2; i++) {
        for (j = 0; j < N + 2; j++) {
            if (i == 0 || i == M + 1 || j == 0 || j == N + 1) {
                printf("█"); // 打印墙壁
                continue;
            }
            if (maze[i - 1][j - 1] == WALL)
                printf("█");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int main()
{
    generate_maze();
    print_maze();
    return 0;
}
