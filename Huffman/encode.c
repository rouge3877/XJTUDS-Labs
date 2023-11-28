#include "encode.h"

// 生成哈夫曼编码，code_table为哈夫曼编码表，index为当前编码的下标，code为当前编码
void createCodeTable(Huffman root, CodeKey2Value *code_table, int index, bool *code)
{
    static int table_index = 0;
    if (root->_left != NULL) {
        code[index] = false;
        createCodeTable(root->_left, code_table, index + 1, code);
    }
    if (root->_right != NULL) {
        code[index] = true;
        createCodeTable(root->_right, code_table, index + 1, code);
    }
    if (root->_left == NULL && root->_right == NULL) {
        code_table[table_index]->_data = root->_data._char;
        code_table[table_index]->_code = (bool *)malloc(sizeof(bool) * index);

        code_table[table_index]->_length = index;

        // printf("<createCodeTable>char:%c(%d)->length%d\n", root->_data._char, root->_data._char, code_table[table_index]->_length);

        for (int i = 0; i < index; i++) {
            code_table[table_index]->_code[i] = code[i];
        }
        table_index++;
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

CodeKey2Value *expandCodeTable(CodeKey2Value *small_table, int size)
{
    CodeKey2Value *expand_table = (CodeKey2Value *)malloc(sizeof(CodeKey2Value) * MAX_CHAR);

    for (int i = 0; i < MAX_CHAR; i++) {
        expand_table[i] = (CodeKey2Value)malloc(sizeof(HuffmanCode));
        expand_table[i]->_data = i;

        expand_table[i]->_length = 0;

        expand_table[i]->_code = NULL;
    }
    for (int i = 0; i < size; i++) {
        expand_table[small_table[i]->_data]->_length = small_table[i]->_length;
        expand_table[small_table[i]->_data]->_code = small_table[i]->_code;
    }

    // for (int i = 0; i < MAX_CHAR; i++) {
    //     if(expand_table[i]->_code!=NULL){
    //         printf("%c(%d)->lentgth:%d\n",expand_table[i]->_data,expand_table[i]->_data,expand_table[i]->_length);
    //     }
    // }

    return expand_table;
}

void writeCodeTable(FILE *output, CodeKey2Value *code_table, int size)
{
    for (int i = 0; i < size; i++) {
        size_t elements_written = fwrite(&code_table[i]->_data, sizeof(ORIGINAL_DATA_TYPE), 1, output);
        if (elements_written != 1) {
            fprintf(stderr, "Have wrong when writting in the output file!\n");
            exit(0);
        }
        elements_written = fwrite(&code_table[i]->_length, sizeof(int), 1, output);
        if (elements_written != 1) {
            fprintf(stderr, "Have wrong when writting in the output file!\n");
            exit(0);
        }
        for (int j = 0; j < code_table[i]->_length; j++) {
            elements_written = fwrite(&code_table[i]->_code[j], sizeof(bool), 1, output);
            if (elements_written != 1) {
                fprintf(stderr, "Have wrong when writting in the output file!\n");
                exit(0);
            }
        }
    }
}

void writeBits(FILE *file, bool *bits, int bitCount)
{
    unsigned char buffer = 0;
    for (int i = 0; i < bitCount; i++) {
        buffer <<= 1;
        if (bits[i]) {
            buffer |= 1;
        }
        if ((i + 1) % 8 == 0) {
            fwrite(&buffer, 1, 1, file);
            buffer = 0;
        }
    }
    // 写入最后一个字节，如果没有完全填满
    if (bitCount % 8 != 0) {
        buffer <<= 8 - bitCount % 8;
        fwrite(&buffer, 1, 1, file);
    }
}

void Huffman_Compress(FILE *input, FILE *output)
{
    // 统计文件字符个数
    int text_char_num = 0;
    // 统计文件中各个字符以及其出现的次数
    CharInfo *text_char_info = CountChar(input, &text_char_num);
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
    size_t elements_written = fwrite(&text_char_num, sizeof(int), 1, output);
    if (elements_written != 1) {
        fprintf(stderr, "Have wrong when writting in the output file!\n");
        exit(0);
    }
    // 写入哈夫曼编码表
    writeCodeTable(output, code_table, text_char_num);

    // 写入文件
    ORIGINAL_DATA_TYPE ch;
    CodeKey2Value *expand_table = expandCodeTable(code_table, text_char_num);
    rewind(input);

    // TODO: write in bit------------------------------------------
    int length = 0;
    bool buffer[8] = {0};
    int index = 0;
    while (fread(&ch, sizeof(ORIGINAL_DATA_TYPE), 1, input)) {
        length += expand_table[ch]->_length;
        for (int i = 0; i < expand_table[ch]->_length; i++) {
            buffer[index] = expand_table[ch]->_code[i];
            index++;
        }
        writeBits(output, expand_table[ch]->_code, expand_table[ch]->_length);
    }

    // 释放内存
    destroyCodeTable(code_table, text_char_num);
    destroyHuffmanTree(huffman);
    free(text_char_info);
    free(code);
    return;
}

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

bool cmpArray(bool *array1, bool *array2, int length)
{
    for (int i = 0; i < length; i++) {
        if (array1[i] != array2[i])
            return false;
    }
    return true;
}

void printBits(unsigned char byte)
{
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
}

// Huffman 解压缩
void Huffman_Uncompress(FILE *input, FILE *output)
{
    unsigned char byte;
    while (fread(&byte, sizeof(unsigned char), 1, input) == 1) {
        // 打印该字节每一位的值
        printBits(byte);
    }
    rewind(input);

    // 读取原始文件字符个数
    int text_char_num;
    fread(&text_char_num, sizeof(int), 1, input);
    printf("the text origin has %d different word\n", text_char_num);
    // 读取哈夫曼编码表
    CodeKey2Value *code_table = readCodeTable(input, text_char_num);

    // 打印编码表查看正确性
    // for (int i = 0; i < text_char_num; i++) {
    //     printf("<Huffman_Uncompress>char:%c(%d)->length%d  and CODEis : ", code_table[i]->_data, code_table[i]->_data, code_table[i]->_length);
    //     for (int j = 0; j < code_table[i]->_length; j++) {
    //         printf("%d", code_table[i]->_code[j]);
    //     }
    //     printf("\n");
    // }

    // 对编码表按照编码长度进行排序
    sortCodeTable(code_table, 0, text_char_num - 1);

    // printf("after sort\n");
    // // 打印编码表查看正确性
    // for (int i = 0; i < text_char_num; i++) {
    //     printf("<Huffman_Uncompress>char:%c(%d)->length%d  and CODEis : ", code_table[i]->_data, code_table[i]->_data, code_table[i]->_length);
    //     for (int j = 0; j < code_table[i]->_length; j++) {
    //         printf("%d", code_table[i]->_code[j]);
    //     }
    //     printf("\n");
    // }

    // 解码

    // TODO: read in bit------------------------------------------
    bool read_bit;
    bool *read_bits_buffer = (bool *)malloc(1 + (code_table[text_char_num - 1]->_length) * sizeof(bool));
    int this_length = 0;
    while (fread(&read_bit, sizeof(bool), 1, input)) {

        printf("%d", this_length);

        read_bits_buffer[this_length] = read_bit;
        this_length++;
        for (int i = 0; i < text_char_num; i++) { // should be quicker
            if (cmpArray(read_bits_buffer, code_table[i]->_code, this_length)) {
                fwrite(&code_table[i]->_data, sizeof(ORIGINAL_DATA_TYPE), 1, output);
                this_length = 0;
                continue;
            }
        }
        if (this_length > code_table[text_char_num - 1]->_length) {
            fprintf(stderr, "Uncompress failed! That is because a wrong encode.\n");
            exit(0);
        }
    }

    if (feof(input)) {
        printf("文件已经读取完毕\n");
    } else {
        printf("发生其他错误\n");
    }

    return;
}