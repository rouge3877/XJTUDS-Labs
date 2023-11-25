#include <stdio.h>
#include <stdlib.h>
#define MAX(A, B) A > B ? A : B
#define MAX_INPUT 10000

typedef struct node {
    int _val;
    struct node *_lchild;
    struct node *_rchild;
    int _height;
} avlnode, *avl;

avl createNode(int val)
{
    avl newnode = (avl)malloc(sizeof(avlnode));
    newnode->_lchild = newnode->_rchild = NULL;
    newnode->_height = 1;
    newnode->_val = val;
    return newnode;
}

int getHeightREAD(avl root)
{
    if (root)
        return root->_height;
    else
        return 0;
}

int getHeight(avl root)
{
    root->_height = MAX(getHeightREAD(root->_lchild), getHeightREAD(root->_rchild)) + 1;
    return root->_height;
}

int balanceFactor(avl root)
{
    if (root)
        return getHeightREAD(root->_lchild) - getHeightREAD(root->_rchild);
    else
        return 0;
}

avl LL_rotation(avl root)
{
    avl new_root = root->_rchild;
    root->_rchild = new_root->_lchild;
    new_root->_lchild = root;
    getHeight(root);
    getHeight(new_root);
    return new_root;
}

avl RR_rotation(avl root)
{
    avl new_root = root->_lchild;
    root->_lchild = new_root->_rchild;
    new_root->_rchild = root;
    getHeight(root);
    getHeight(new_root);
    return new_root;
}

avl insertNode(avl root, int val)
{
    if (!root)
        return createNode(val);
    else if (val < root->_val)
        root->_lchild = insertNode(root->_lchild, val);
    else if (val > root->_val)
        root->_rchild = insertNode(root->_rchild, val);
    else {
        fprintf(stderr, "The avl %d is existed!\n", val);
        return root;
    }

    getHeight(root);

    int balance = balanceFactor(root);
    if (balance > 1 && balanceFactor(root->_lchild) > 0) {
        root = RR_rotation(root);
    } else if (balance > 1 && balanceFactor(root->_lchild) < 0) {
        root->_lchild = LL_rotation(root->_lchild);
        root = RR_rotation(root);
    } else if (balance < -1 && balanceFactor(root->_rchild) > 0) {
        root->_rchild = RR_rotation(root->_rchild);
        root = LL_rotation(root);
    } else if (balance < -1 && balanceFactor(root->_rchild) < 0) {
        root = LL_rotation(root);
    }

    return root;
}

// 计算查找长度
double _AverageSearchPath(avl T, int level)
{
    if (T == NULL)
        return 0;
    double sum = 0;
    sum += level;
    sum += _AverageSearchPath(T->_lchild, level + 1);
    sum += _AverageSearchPath(T->_rchild, level + 1);
    return sum;
}

// 计算平均查找长度
double AverageSearchPath(avl T, int n)
{
    return _AverageSearchPath(T, 1) / n;
}

void layerOrderPut(avl root)
{
    avl a[MAX_INPUT] = {0};
    int top = 0;
    int end = 0;
    a[top] = root;
    top++;
    while (top - end > 0) {
        avl this_root = a[end];
        end++;
        if (this_root->_lchild) {
            a[top] = this_root->_lchild;
            top++;
        }
        if (this_root->_rchild) {
            a[top] = this_root->_rchild;
            top++;
        }
        printf("%d ", this_root->_val);
    }
}

int getData(int **data)
{
    *data = (int *)malloc(sizeof(int) * MAX_INPUT);
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

void question1(avl *T, int *count_ptr)
{
    printf("-------------QUESTION 1-------------\n");
    int *data;
    *count_ptr = getData(&data); // 获得数列数据和数列长度
    for (int i = 0; i < *count_ptr; i++) {
        *T = insertNode(*T, data[i]);
    }
    return;
}

void question2(avl T, int num){
    printf("\n");
    printf("-------------QUESTION 2-------------\n");
    double average = AverageSearchPath(T, num);
    printf("平均查找长度：%lf\n", average);
    
    printf("\n----------------END.----------------\n");
    return;

}


int main(void)
{
    avl root = NULL;
    int count = 0;
    question1(&root, &count);
    question2(root, count);
    
    return 0;
}