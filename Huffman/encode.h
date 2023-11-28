#ifndef _ENCODE_H_
#define _ENCODE_H_

#include "huffman.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// 哈夫曼编码结构
typedef struct Code {
    ORIGINAL_DATA_TYPE _data;
    int _length;
    bool *_code;
} HuffmanCode, *pHuffmanCode, *CodeKey2Value;

void Huffman_Compress(FILE *input, FILE *output);

void Huffman_Uncompress(FILE *input, FILE *output);

#endif