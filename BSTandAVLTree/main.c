// main.c
#include "BSTree.h"

int main()
{
    BSTree T = NULL;
    int data[] = {5, 3, 6, 7, 1, 9, 8};
    int n = sizeof(data) / sizeof(int);

    CreateBST(&T, data, n);
    printf("中序遍历：\n");
    InOrderTraverse(T);
    printf("\n平均查找长度：%lf\n", AverageSearchPath(T, n));

    printf("删除节点6：\n");
    DeleteNode(&T, 6);
    InOrderTraverse(T);

    return 0;
}
