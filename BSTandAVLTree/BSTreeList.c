#include "BSTreeList.h"

void CreateBST(BSTree *T, int* data, int n) {
    for (int i = 0; i < MAX_SIZE; i++) {
        (*T)[i].data = EMPTY;
        (*T)[i].exist = false;
    }
    for (int i = 0; i < n; i++) {
        int j = 0;
        while ((*T)[j].exist && (*T)[j].data != data[i]) {
            if (data[i] < (*T)[j].data) {
                if (2 * j + 1 >= MAX_SIZE) break;
                j = 2 * j + 1;
            } else {
                if (2 * j + 2 >= MAX_SIZE) break;
                j = 2 * j + 2;
            }
        }
        if (!(*T)[j].exist && j < MAX_SIZE) {
            (*T)[j].data = data[i];
            (*T)[j].exist = true;
        }
    }
}

void InOrderTraverseCore(BSTree T, int position) {
    if (T[position].exist) {
        InOrderTraverseCore(T, 2 * position + 1);
        printf("%d ", T[position].data);
        InOrderTraverseCore(T, 2 * position + 2);
    }
}

void InOrderTraverse(BSTree T){
    InOrderTraverseCore(T, 0);
    printf("\n");
}

double AverageSearchPath(BSTree T, int size) {
    int count = 0, depthSum = 0;
    for (int i = 0; i < size; i++) {
        int position = 0;
        int depth = 0;
        while (T[position].exist && T[position].data != i) {
            if (i < T[position].data) {
                position = 2 * position + 1;
            } else if (i > T[position].data) {
                position = 2 * position + 2;
            }
            depth++;
        }
        if (T[position].exist && T[position].data == i) {
            depthSum += depth;
            count++;
        }
    }
    return (double)depthSum / count;
}

void DeleteNode(BSTree *T, int key, bool *delete_success) {
    int position = 0;
    while ((*T)[position].exist && (*T)[position].data != key) {
        if (key < (*T)[position].data) {
            position = 2 * position + 1;
        } else {
            position = 2 * position + 2;
        }
    }
    if ((*T)[position].exist && (*T)[position].data == key) {
        (*T)[position].data = EMPTY;
        (*T)[position].exist = false;
        *delete_success = true;
        int left = 2 * position + 1;
        int right = 2 * position + 2;
        if ((*T)[right].exist) {
            (*T)[position].data = (*T)[right].data;
            DeleteNode(T, (*T)[right].data, delete_success);
        } else if ((*T)[left].exist) {
            (*T)[position].data = (*T)[left].data;
            DeleteNode(T, (*T)[left].data, delete_success);
        }
    } else {
        *delete_success = false;
    }
}
