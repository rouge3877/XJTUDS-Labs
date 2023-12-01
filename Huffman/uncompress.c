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

// hash
void create_hash_table(HashTable *my_hash_table, CodeKey2Value *code_table, int size)
{
    for (int i = 0; i < size; i++) {
        HashKey hash_key;
        hash_key._length = code_table[i]->_length;
        hash_key._code = code_table[i]->_code;
        insertHashTable(hash_key, code_table[i]->_data, my_hash_table);
    }
}

// Huffman 解压缩，注意正文部分是按字节写入的
void Huffman_Uncompress(FILE *input, FILE *output)
{
    int text_diff_char_num;
    fread(&text_diff_char_num, sizeof(int), 1, input);
    printf("the text origin has %d different word\n", text_diff_char_num);
    int text_ch_num;
    fread(&text_ch_num, sizeof(int), 1, input);
    printf("the text origin has %d word\n", text_ch_num);
    // 读取哈夫曼编码表
    CodeKey2Value *code_table = readCodeTable(input, text_diff_char_num);

    // printf("Here is the context:");
    // __uint8_t byte;
    // while (fread(&byte, 1, 1, input) == 1) {
    //     // 打印该字节每一位的值
    //     bool *bool_list = byte2BoolList(byte);
    //     for (int i = 0; i < 8; i++) {
    //         printf("%d", bool_list[i]);
    //     }
    //     free(bool_list);
    // }
    // rewind(input);
    // printf("\nfinish!\n\n");

    // 打印编码表查看正确性--------------------------------------------------------------
    for (int i = 0; i < text_diff_char_num; i++) {
        printf("<Huffman_Uncompress>char:%c(%d)->length%d  and CODEis : ", code_table[i]->_data, code_table[i]->_data, code_table[i]->_length);
        for (int j = 0; j < code_table[i]->_length; j++) {
            printf("%d", code_table[i]->_code[j]);
        }
        printf("\n");
    }
    // // 对编码表按照编码长度进行排序
    // sortCodeTable(code_table, 0, text_diff_char_num - 1);
    // printf("after sort\n");
    // // 打印编码表查看正确性
    // for (int i = 0; i < text_diff_char_num; i++) {
    //     printf("<Huffman_Uncompress>char:%c(%d)->length%d  and CODEis : ", code_table[i]->_data, code_table[i]->_data, code_table[i]->_length);
    //     for (int j = 0; j < code_table[i]->_length; j++) {
    //         printf("%d", code_table[i]->_code[j]);
    //     }
    //     printf("\n\n");
    // }
    // -----------------------------------------------------------------------------------

    // 寻找最大编码长度
    int max_code_length = -1;
    for (int i = 0; i < text_diff_char_num; i++) {
        if (code_table[i]->_length > max_code_length)
            max_code_length = code_table[i]->_length;
    }
    printf("\nmax_code_length is %d\n", max_code_length);

    // 建立一个哈希表，一个从length和code array 到char 的哈希表。
    HashTable my_hash_table[HASH_TABLE_SIZE];
    create_hash_table(my_hash_table, code_table, text_diff_char_num);

    // 先将所有的编码读入到一个buffer中
    bool *read_buffer = (bool *)malloc(sizeof(bool) * BUFFER_MAX_FILE_SIZE * max_code_length + 8);
    int buffer_index = 0;
    __uint8_t byte;
    while (fread(&byte, 1, 1, input) == 1) {
        // 打印该字节每一位的值
        bool *bool_list = byte2BoolList(byte);
        for (int i = 0; i < 8; i++) {
            read_buffer[buffer_index++] = bool_list[i];
        }
        free(bool_list);
    }
    if (feof(input))
        printf("文件已经读取完毕\n");
    else
        printf("发生其他错误\n");

    // 打印buffer
    printf("buffer is :\n");
    for (int i = 0; i < buffer_index; i++) {
        printf("%d", read_buffer[i]);
    }
    printf("\n");

    // 从buffer中读取编码,开始处理buffer
    int buffer_read_index = 0;
    int decode_num = 0;
    int this_length = 1;
    bool *this_list = read_buffer;
    // 开始解码
    while (true) {
        // 从哈希表中查找
        HashKey hash_key;
        hash_key._length = this_length;
        hash_key._code = this_list;
        ORIGINAL_DATA_TYPE hash_value = searchHashTable(hash_key, my_hash_table);
        if (hash_value != 0) {
            // 找到了
            printf("find %c\n", hash_value);
            fwrite(&hash_value, sizeof(ORIGINAL_DATA_TYPE), 1, output);
            decode_num++;
            if (decode_num == text_ch_num) {
                printf("decode over\n");
                break;
            }
            buffer_read_index++;
            // 重置
            this_length = 1;
            this_list = read_buffer + buffer_read_index;
        } else {
            // 没找到
            printf("not find\n");
            this_length++;
            buffer_read_index++;
        }

        // 判断是否读取完毕(超限)
        if (buffer_read_index >= buffer_index) {
            printf("buffer is over\n");
            break;
        }
    }

    // 释放内存
    for (int i = 0; i < text_diff_char_num; i++) {
        free(code_table[i]->_code);
        free(code_table[i]);
    }
    free(code_table);
    free(read_buffer);

    return;
}
