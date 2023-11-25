#include "BSTreeList.h"

BSTree initBSTree(int capacity)
{
    BSTree T = (BSTree)malloc(sizeof(struct BST));
    T->_data = (DataType *)malloc(sizeof(DataType) * capacity);
    for (int i = 0; i < capacity; i++)
        T->_data[i] = EMPTY;
    T->_size = 0;
    T->_capacity = capacity;
    return T;
}

// 二叉搜索树插入数据
void InsertBST(BSTree T, DataType x)
{
    int index = 0;

    while (T->_data[index] != EMPTY && index < T->_capacity) {
        if (x < T->_data[index])
            index = 2 * index + 1; // 左孩子
        else if (x > T->_data[index])
            index = 2 * index + 2; // 右孩子
        else
            return; // BST不允许重复元素插入，故直接返回
    }

    if (index < T->_capacity) {
        T->_data[index] = x;
        T->_size++;
    }
}

void CreateBST(BSTree *T, DataType *data, int n)
{
    *T = initBSTree(MAX_CAPACITY);
    int i;
    for (i = 0; i < n; i++) {
        InsertBST(*T, data[i]);
    }
}

void _InOrderTraverse(BSTree T, int index)
{
    if (index < T->_capacity && T->_data[index] != EMPTY) {
        _InOrderTraverse(T, 2 * index + 1);
        printf("%d ", T->_data[index]);
        _InOrderTraverse(T, 2 * index + 2);
    }
}

void InOrderTraverse(BSTree T)
{
    _InOrderTraverse(T, 0);
}

// 计算二叉排序树T查找成功的平均查找长度
double AverageSearchPath(BSTree T, int n)
{
    double sum = 0;
    for (int i = 0; i < T->_capacity; i++) {
        if (T->_data[i] != EMPTY) {
            int level = 1;
            int index = i;
            while (index != 0) {
                index = (index - 1) / 2;
                level++;
            }
            sum += level;
        }
    }
    return sum / n;
}

// 删除二叉排序树T中的关键字为key的结点
void _DeleteNode(BSTree *T, DataType key, int index, bool *delete_success)
{
    if (index < (*T)->_capacity && (*T)->_data[index] != EMPTY) {
        if (key == (*T)->_data[index]) {
            if ((*T)->_data[2 * index + 1] == EMPTY && (*T)->_data[2 * index + 2] == EMPTY) {
                (*T)->_data[index] = EMPTY;
                (*T)->_size--;
            } else if ((*T)->_data[2 * index + 1] != EMPTY && (*T)->_data[2 * index + 2] == EMPTY) {
                (*T)->_data[index] = (*T)->_data[2 * index + 1];
                _DeleteNode(T, (*T)->_data[2 * index + 1], 2 * index + 1, delete_success);
            } else if ((*T)->_data[2 * index + 1] == EMPTY && (*T)->_data[2 * index + 2] != EMPTY) {
                (*T)->_data[index] = (*T)->_data[2 * index + 2];
                _DeleteNode(T, (*T)->_data[2 * index + 2], 2 * index + 2, delete_success);
            } else {
                int min_index = 2 * index + 2;
                while ((*T)->_data[min_index] != EMPTY && min_index < (*T)->_capacity) {
                    min_index = 2 * min_index + 1;
                }
                min_index = (min_index - 1) / 2;
                (*T)->_data[index] = (*T)->_data[min_index];
                _DeleteNode(T, (*T)->_data[min_index], min_index, delete_success);
            }
        } else if (key < (*T)->_data[index]) {
            _DeleteNode(T, key, 2 * index + 1, delete_success);
        } else {
            _DeleteNode(T, key, 2 * index + 2, delete_success);
        }
    }
}

void DeleteNode(BSTree *T, DataType key, bool *delete_success)
{
    _DeleteNode(T, key, 0, delete_success);
}

// 测试
/*
int main(void)
{
    int a[8] = {50, 26, 66, 22, 30, 60, 70, 68};
    BSTree T = NULL;
    CreateBST(&T, a, 8);
    InOrderTraverse(T);

    double res = AverageSearchPath(T, 8);
    bool delete_success = 1;
    DeleteNode(&T, 50, &delete_success);
    InOrderTraverse(T);

    return 0;
}
*/