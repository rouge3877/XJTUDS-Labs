#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    /* data */
    struct node *_lchild;
    struct node *_rchild;
    int _choose_sum;
    int _level;
} choose_tree_node, *ptr_node;

ptr_node createNode(int level)
{
    ptr_node create_node = (ptr_node)malloc(sizeof(choose_tree_node));
    create_node->_lchild = create_node->_rchild = NULL;
    create_node->_level = level;
    create_node->_choose_sum = 0;
    return create_node;
}

void addNode(ptr_node parent_node, int level)
{
    parent_node->_lchild = createNode(level);
    parent_node->_lchild->_choose_sum = parent_node->_choose_sum + level * 1;

    parent_node->_rchild = createNode(level);
    parent_node->_rchild->_choose_sum = parent_node->_choose_sum + level * 0;
    return;
}

void makeChooseTree(ptr_node root, int *list, int target, bool *path, int start)
{
    if (*list == -1)
        return;
    if (root->_lchild == NULL && root->_rchild == NULL)
        addNode(root, *list);

    if (root->_lchild->_choose_sum < target) {
        path[start] = 1;
        makeChooseTree(root->_lchild, list + 1, target, path, start + 1);
    } else if (root->_lchild->_choose_sum == target) {
        path[start] = 1;
        for (int i = 0; i < 6; i++)
            printf("%d ", path[i]);
    }

    if (root->_rchild->_choose_sum < target) {
        path[start] = 0;
        makeChooseTree(root->_rchild, list + 1, target, path, start + 1);
    } else if (root->_rchild->_choose_sum == target) {
        path[start] = 0;
        for (int i = 0; i < 6; i++)
            printf("%d ", path[i]);
    }
    return;
}

int main(void)
{

    ptr_node root = createNode(0);
    bool path[6] = {0, 0, 0, 0, 0, 0};
    int list[7] = {1, 8, 4, 3, 5, 2, -1};
    makeChooseTree(root, list, 10, path, 0);

    return 0;
}