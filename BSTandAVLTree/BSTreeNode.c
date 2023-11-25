// BSTree.c
#include "BSTreeNode.h"

//插入节点
void InsertBST(BSTree *T, int x){
    if(*T == NULL){
        *T = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = x;
        (*T)->count = 1;
        (*T)->lchild = (*T)->rchild = NULL;
    }else if(x == (*T)->data){
        (*T)->count++;
    }else if(x < (*T)->data){
        InsertBST(&((*T)->lchild), x);
    }else{
        InsertBST(&((*T)->rchild), x);
    }
}

//创建二叉排序树
void CreateBST(BSTree *T, int *data, int n){
    *T = NULL;
    int i;
    for(i = 0; i < n; i++){
        InsertBST(T, data[i]);
    }
}

// 中序遍历
void InOrderTraverse(BSTree T){
    if(T != NULL){
        InOrderTraverse(T->lchild);
        printf("%d ", T->data);
        InOrderTraverse(T->rchild);
    }
}

// 计算平均查找路径长度
double AverageSearchPath(BSTree T, int n){
    if(T == NULL)
        return 0;
    else
        return ((T->count * 2 - 1) + AverageSearchPath(T->lchild, n) + AverageSearchPath(T->rchild, n)) / n;
}

//删除节点
void DeleteNode(BSTree *T, int x, _Bool * ret){
    if(*T == NULL){
        printf("无%d", x);
        *ret = 0;
        return ;
    } else if(x < (*T)->data){
        DeleteNode(&(*T)->lchild, x, ret);
    } else if(x > (*T)->data){
        DeleteNode(&(*T)->rchild, x, ret);
    } else {  // 找到该节点
        // 如果左右子树都不为空
        if((*T)->lchild && (*T)->rchild){
            BSTree tmp = (*T)->lchild;
            while(tmp->rchild){
                tmp = tmp->rchild;  // 找到左子树的最右节点，即左子树的最大值
            }
            (*T)->data = tmp->data;  // 用该值覆盖要删除的节点
            DeleteNode(&(*T)->lchild, tmp->data, ret);  // 在左子树中删除该节点
        } else {  // 左右子树至少有一个为空
            BSTree tmp = *T;  
            if((*T)->lchild == NULL){  // 没有左子树
                *T = (*T)->rchild;
            } else if((*T)->rchild == NULL){  // 没有右子树
                *T = (*T)->lchild;
            }
            free(tmp);
        }
    }
}
