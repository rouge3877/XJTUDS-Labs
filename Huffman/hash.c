#include "hash.h"

bool cmpArray(bool *array1, bool *array2, int length)
{
    for (int i = 0; i < length; i++) {
        if (array1[i] != array2[i])
            return false;
    }
    return true;
}

unsigned long hash(HashKey key)
{
    unsigned long hash = HASH_INIT;
    for (int i = 0; i < key._length; ++i) {
        // 将bool值转换为整数 (0 或 1)，然后参与哈希计算
        hash = (((hash << 5) + hash) + (key._code[i] ? 1 : 0)) % HASH_TABLE_SIZE;
    }
    return hash;
}

void insertHashTable(HashKey key, ORIGINAL_DATA_TYPE value, HashTable my_hash_table[])
{
    unsigned long index = hash(key);
    struct HashNode *node = malloc(sizeof(struct HashNode));

    // 为key._code创建一份新的副本
    bool *code_copy = malloc(sizeof(bool) * key._length);
    memcpy(code_copy, key._code, sizeof(bool) * key._length);

    node->key._length = key._length;
    node->key._code = code_copy;

    node->value = value;
    node->next = my_hash_table[index];
    my_hash_table[index] = node;
}

ORIGINAL_DATA_TYPE searchHashTable(HashKey key, HashTable my_hash_table[])
{
    unsigned long index = hash(key);
    struct HashNode *node = my_hash_table[index];
    
    while (node != NULL) {
        if (node->key._length == key._length && cmpArray(node->key._code, key._code, key._length))
            return node->value;
        node = node->next;
    }
    // Key not found
    // fprintf(stderr, "Key not found\n");
    return 0;
}

void cleanHashTable(HashTable my_hash_table[])
{
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        struct HashNode *node = my_hash_table[i];
        while (node != NULL) {
            struct HashNode *temp = node;
            node = node->next;

            free(temp->key._code); // 释放bool数组副本
            free(temp);
        }
    }
}
