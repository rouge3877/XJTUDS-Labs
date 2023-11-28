#include "encode.h"

void createCodeTable(Huffman root, CodeKey2Value *code_table, int index, bool *code) // 生成哈夫曼编码，code_table为哈夫曼编码表，index为当前编码的下标，code为当前编码
{
    if (root->_left != NULL) {
        code[index] = false;
        createCodeTable(root->_left, code_table, index + 1, code);
    }
    if (root->_right != NULL) {
        code[index] = true;
        createCodeTable(root->_right, code_table, index + 1, code);
    }
    if (root->_left == NULL && root->_right == NULL) {
        code_table[root->_data._char]->_data = root->_data._char;
        code_table[root->_data._char]->_code = (bool *)malloc(sizeof(bool) * index);
        code_table[root->_data._char]->_length = index;
        for (int i = 0; i < index; i++) {
            code_table[root->_data._char]->_code[i] = code[i];
        }
    }
    return;
}

void destroyCodeTable(CodeKey2Value *code_table, int size)
{
    for (int i = 0; i < size; i++) {
        free(code_table[i]->_code);
        free(code_table[i]);
    }
    free(code_table);
}

void writeCodeTable(FILE *output, CodeKey2Value *code_table, int size)
{
    for (int i = 0; i < size; i++) {
        fwrite(&code_table[i]->_data, sizeof(ORIGINAL_DATA_TYPE), 1, output);
        fwrite(&code_table[i]->_length, sizeof(int), 1, output);
        for (int j = 0; j < code_table[i]->_length; j++) {
            fwrite(&code_table[i]->_code[j], sizeof(bool), 1, output);
        }
    }
}

void Huffman_Compress(FILE *input, FILE *output)
{
    // 统计文件字符个数
    int text_char_num = CountCharNum(input);
    // 统计文件中各个字符以及其出现的次数
    CharInfo *text_char_info = CountChar(input,text_char_num);
    // 创建哈夫曼树
    Huffman huffman = createHuffmanTree(text_char_info, text_char_num);
    // 创建哈夫曼编码表
    CodeKey2Value *code_table = (CodeKey2Value *)malloc(sizeof(CodeKey2Value) * text_char_num);
    for (int i = 0; i < text_char_num; i++) {
        code_table[i] = (CodeKey2Value)malloc(sizeof(HuffmanCode));
    }
    int max_depth = findMaxDepth(huffman);
    bool *code = (bool *)malloc(sizeof(bool) * max_depth + 1);
    createCodeTable(huffman, code_table, 0, code);

    // 写入文件
    // 写入原始文件字符个数
    fwrite(&text_char_num, sizeof(int), 1, output);
    // 写入哈夫曼编码表
    writeCodeTable(output, code_table, text_char_num);
    // 写入文件
    ORIGINAL_DATA_TYPE ch;
    while (fread(&ch, sizeof(ORIGINAL_DATA_TYPE), 1, input)) {
        for (int i = 0; i < code_table[ch]->_length; i++) {
            fwrite(&code_table[ch]->_code[i], sizeof(bool), 1, output);
        }
    }
    // 释放内存
    // destroyCodeTable(code_table, text_char_num);
    // destroyHuffmanTree(huffman);
    // free(text_char_info);
    // free(code);
    return;
}

CodeKey2Value *readCodeTable(FILE *input, int *size)
{
    CodeKey2Value *code_table = (CodeKey2Value *)malloc(sizeof(CodeKey2Value) * MAX_CHAR);
    ORIGINAL_DATA_TYPE ch;
    int length;
    bool code;
    int index = 0;
    while (fread(&ch, sizeof(ORIGINAL_DATA_TYPE), 1, input)) {
        fread(&length, sizeof(int), 1, input);
        code_table[index] = (CodeKey2Value)malloc(sizeof(HuffmanCode));
        code_table[index]->_data = ch;
        code_table[index]->_length = length;
        code_table[index]->_code = (bool *)malloc(sizeof(bool) * length);
        for (int i = 0; i < length; i++) {
            fread(&code, sizeof(bool), 1, input);
            code_table[index]->_code[i] = code;
        }
        index++;
    }
    *size = index;
    return code_table;
}

void Huffman_Uncompress(FILE *input, FILE *output)
{
    // 读取原始文件字符个数
    int text_char_num;
    fread(&text_char_num, sizeof(int), 1, input);
    // 读取哈夫曼编码表
    int code_table_size;
    CodeKey2Value *code_table = readCodeTable(input, &code_table_size);
    // 读取文件
    ORIGINAL_DATA_TYPE ch;
    int index = 0;
    int count = 0;
    bool code;
    CharInfo zero = {0, 0};
    Huffman root = createHuffmanNode(zero, 0);
    Huffman cur = root;
    while (fread(&code, sizeof(bool), 1, input)) {
        if (code) {
            cur = cur->_right;
        } else {
            cur = cur->_left;
        }
        if (cur->_left == NULL && cur->_right == NULL) {
            fwrite(&cur->_data._char, sizeof(ORIGINAL_DATA_TYPE), 1, output);
            cur = root;
            count++;
        }
        if (count == text_char_num) {
            break;
        }
    }
    // 释放内存
    destroyHuffmanTree(root);
    destroyCodeTable(code_table, code_table_size);
    return;
}