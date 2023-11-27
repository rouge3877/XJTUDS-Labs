#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHAR 256

typedef struct Node {
    unsigned char symbol;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    Node* data[MAX_CHAR];
    int count;
} Heap;

void Huffman_Compress(FILE *input, FILE *output);

void Huffman_Uncompress(FILE *input, FILE *output);

#endif
