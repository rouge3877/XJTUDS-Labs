#ifndef _BSTREE_LIST_H
#define _BSTREE_LIST_H

#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1000
#define EMPTY -1001

typedef struct node{
    bool exist;  // Existence of node
    int data;  // Node data
} BSTNode;

typedef BSTNode BSTree[MAX_SIZE];

void CreateBST(BSTree *T, int* data, int n);
void InOrderTraverse(BSTree T);
double AverageSearchPath(BSTree T, int size);
void DeleteNode(BSTree *T, int key, bool *delete_success);

#endif /*_BSTREE_LIST_H*/

