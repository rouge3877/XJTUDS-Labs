#ifndef _BSTREE_LIST_H
#define _BSTREE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_CAPACITY 1024
#define EMPTY -1

typedef int DataType;

typedef struct BST{
    DataType *_data;
    int _size; // currently used size
    int _capacity;  // total capacity
} *BSTree;

void CreateBST(BSTree *T, DataType *data, int n);
void InOrderTraverse(BSTree T);
double AverageSearchPath(BSTree T, int size);
void DeleteNode(BSTree *T, DataType key, _Bool *delete_success);

#endif /*_BSTREE_LIST_H*/