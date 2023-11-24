#ifndef _B_STREE_H_
#define _B_STREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode{
    int data;
    int count;  // 记录该节点被访问的次数
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

void CreateBST(BSTree *T, int *data, int n);  // 创建二叉排序树
void InOrderTraverse(BSTree T);  // 中序遍历二叉排序树
double AverageSearchPath(BSTree T, int n);  // 计算平均查找长度
void DeleteNode(BSTree *T, int x);  // 删除包含x的节点

#endif  // _B_STREE_H_
