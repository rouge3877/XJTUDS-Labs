#include "count.h"

// 统计文件中各个字符以及其出现的次数
CharInfo *CountChar(FILE *fp,int length) {
    CharInfo *char_list = (CharInfo *) malloc(sizeof(CharInfo) * length);
    for (int i = 0; i < MAX_CHAR; ++i) {
        char_list[i]._char = i;
        char_list[i]._frequency = 0;
    }
    ORIGINAL_DATA_TYPE ch;
    while ((ch = fgetc(fp)) != EOF) {
        char_list[ch]._frequency++;
    }
    return char_list;
}

// 统计文件字符个数
int CountCharNum(FILE *fp) {
    int count = 0;
    ORIGINAL_DATA_TYPE ch;
    while ((ch = fgetc(fp)) != EOF) {
        count++;
    }
    if(count == 0) {
        fprintf(stderr,"Input File is empty\n");
        exit(0);
    }
    return count;
}
