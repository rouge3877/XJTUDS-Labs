#include <stdio.h>
#include <stdlib.h>
#define MAX(A, B) A > B ? A : B

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

void layerOrderPut(avl root)
{
    avl a[10000] = {0};
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

int main(void)
{
    avl root = NULL;
    int insert[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        root = insertNode(root, insert[i]);
    }

    layerOrderPut(root);
    return 0;
}