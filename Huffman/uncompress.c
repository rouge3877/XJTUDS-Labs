#include "encode.h"

CodeKey2Value *readCodeTable(FILE *input, int size)
{
    CodeKey2Value *code_table = (CodeKey2Value *)malloc(sizeof(CodeKey2Value) * size);
    for (int i = 0; i < size; i++) {
        code_table[i] = (CodeKey2Value)malloc(sizeof(HuffmanCode));
        size_t elements_read = fread(&code_table[i]->_data, sizeof(ORIGINAL_DATA_TYPE), 1, input);
        if (elements_read != 1) {
            fprintf(stderr, "Have wrong when reading in the input file!\n");
            exit(0);
        }
        elements_read = fread(&code_table[i]->_length, sizeof(int), 1, input);
        if (elements_read != 1) {
            fprintf(stderr, "Have wrong when reading in the input file!\n");
            exit(0);
        }
        code_table[i]->_code = (bool *)malloc(sizeof(bool) * code_table[i]->_length);
        for (int j = 0; j < code_table[i]->_length; j++) {
            elements_read = fread(&code_table[i]->_code[j], sizeof(bool), 1, input);
            if (elements_read != 1) {
                fprintf(stderr, "Have wrong when reading in the input file!\n");
                exit(0);
            }
        }
    }
    return code_table;
}

// 对编码表按照编码长度进行排序(使用快速排序)
void sortCodeTable(CodeKey2Value *code_table, int left, int right)
{
    if (left >= right) {
        return;
    }
    int i = left, j = right;
    CodeKey2Value temp = code_table[left];
    while (i < j) {
        while (i < j && code_table[j]->_length >= temp->_length) {
            j--;
        }
        code_table[i] = code_table[j];
        while (i < j && code_table[i]->_length <= temp->_length) {
            i++;
        }
        code_table[j] = code_table[i];
    }
    code_table[i] = temp;
    sortCodeTable(code_table, left, i - 1);
    sortCodeTable(code_table, i + 1, right);
}

// 比较两个数组是否相等（在length范围内）
bool cmpArray(bool *array1, bool *array2, int length)
{
    for (int i = 0; i < length; i++) {
        if (array1[i] != array2[i])
            return false;
    }
    return true;
}

// 合并两个数组，将small_array合并到big_array中，其中会从big_array的big_index开始
void mergeArray(bool *big_array, bool *small_array, int length, int big_index)
{
    for (int i = 0; i < length; i++) {
        big_array[big_index + i] = small_array[i];
    }
}

// 将一个byte转化为bool数组（记得free）
bool *byte2BoolList(__uint8_t byte)
{
    bool *bool_list = (bool *)malloc(sizeof(bool) * 8);
    for (int i = 0; i < 8; i++) {
        bool_list[7 - i] = byte & 1;
        byte = byte >> 1;
    }
    return bool_list;
}

// Huffman 解压缩，注意正文部分是按字节写入的
void Huffman_Uncompress(FILE *input, FILE *output)
{
    __uint8_t byte;
    while (fread(&byte, sizeof(unsigned char), 1, input) == 1) {
        // 打印该字节每一位的值
        bool *bool_list = byte2BoolList(byte);
        for(int i=0;i<8;i++){
            printf("%d",bool_list[i]);
        }
    }
    rewind(input);

    // 读取原始文件不同字符个数
    int text_diff_char_num;
    fread(&text_diff_char_num, sizeof(int), 1, input);
    printf("the text origin has %d different word\n", text_diff_char_num);
    // 读取哈夫曼编码表
    CodeKey2Value *code_table = readCodeTable(input, text_diff_char_num);

    // 打印编码表查看正确性--------------------------------------------------------------
    for (int i = 0; i < text_diff_char_num; i++) {
        printf("<Huffman_Uncompress>char:%c(%d)->length%d  and CODEis : ", code_table[i]->_data, code_table[i]->_data, code_table[i]->_length);
        for (int j = 0; j < code_table[i]->_length; j++) {
            printf("%d", code_table[i]->_code[j]);
        }
        printf("\n");
    }
    // 对编码表按照编码长度进行排序
    sortCodeTable(code_table, 0, text_diff_char_num - 1);
    printf("after sort\n");
    // 打印编码表查看正确性
    for (int i = 0; i < text_diff_char_num; i++) {
        printf("<Huffman_Uncompress>char:%c(%d)->length%d  and CODEis : ", code_table[i]->_data, code_table[i]->_data, code_table[i]->_length);
        for (int j = 0; j < code_table[i]->_length; j++) {
            printf("%d", code_table[i]->_code[j]);
        }
        printf("\n\n");
    }
    // -----------------------------------------------------------------------------------

    // 寻找最大编码长度
    int max_code_length = -1;
    for (int i = 0; i < text_diff_char_num; i++) {
        if (code_table[i]->_length > max_code_length)
            max_code_length = code_table[i]->_length;
    }
    printf("\nmax_code_length is %d\n", max_code_length);

    // TODO: read in bit------------------------------------------
    bool *buffer_read = (bool *)malloc(sizeof(bool) * max_code_length);
    __uint8_t byte_read;
    while (fread(&byte_read, sizeof(__uint8_t), 1, input) == 1) {
        // 解码时需要建立一个哈希表，一个从length和code array 到char 的哈希表。
        // 然后每次读入一个bit，然后在哈希表中查找，如果找到了，就输出，然后清空buffer，继续读入bit。
    }

    printf("Here!!");
    if (feof(input)) {
        printf("文件已经读取完毕\n");
    } else {
        printf("发生其他错误\n");
    }

    return;
}
