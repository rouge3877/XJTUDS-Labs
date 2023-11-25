// main.c
#include "BSTreeList.h"
#define DATASIZE 1000

int getData(DataType **);
void question1(BSTree *, DataType *);
void question2(BSTree);
void question3(BSTree, int);
void question4(BSTree);

int main(void)
{
    BSTree T = NULL;
    int count = 0;
    question1(&T, &count);
    question2(T);
    question3(T, count);
    question4(T);

    return 0;
}

int getData(DataType **data)
{
    *data = (DataType*)malloc(sizeof(DataType) * 100); // 假设最多输入100个数，如果会超过此数，应采用动态扩展数组的方式
    int count = 0;
    int tmp;
    char c;
    printf("请输入数列，以回车结束：\n");

    while (scanf("%d", &tmp)) { // 读取输入的数字
        (*data)[count++] = tmp; // 存入数组
        c = getchar();          // 看下一个字符是否是'\n'
        if (c == '\n') {
            break; // 如果是'\n'，则结束输入
        }
    }
    return count;
}
void question1(BSTree *T, int *count_ptr)
{
    printf("-------------QUESTION 1-------------\n");
    DataType *data;
    *count_ptr = getData(&data); // 获得数列数据和数列长度
    CreateBST(T, data, *count_ptr);

    return;
}
void question2(BSTree T)
{
    printf("\n");
    printf("-------------QUESTION 2-------------\n");
    printf("中序遍历：\n");
    InOrderTraverse(T);
    printf("\n");
    return;
}
void question3(BSTree T, int n)
{
    printf("\n");
    printf("-------------QUESTION 3-------------");
    printf("\n平均查找长度：%lf\n", AverageSearchPath(T, n));
    return;
}
void question4(BSTree T)
{
    printf("\n");
    printf("-------------QUESTION 4-------------\n");
    printf("键入需要查找并删除的节点：\n");
    DataType key;
    scanf("%d", &key);
    bool delete_re = 1;
    DeleteNode(&T, key, &delete_re);
    if (delete_re) {
        printf("删除%d后中序遍历：\n", key);
        InOrderTraverse(T);
    }
    printf("\n----------------END.----------------\n");
    return;
}
