#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int _key;
    int _id;
    struct node* _next;
} node, *ptr_node;

void insertNode(node* pre_node, node* insert_node){
    pre_node->_next = insert_node;
}

node* createNode(int key, int id){
    node* create_node = (node*)malloc(sizeof(node));
    create_node->_id = id;
    create_node->_key = key;
    create_node->_next = NULL;
    return create_node;
}

int deleteNextNode(node* pre_node){
    if(pre_node->_next == pre_node){
        return -1;
    }else{
        ptr_node temp = pre_node->_next;
        pre_node->_next = temp->_next;
        int ret_key = temp->_key; 
        return ret_key;     
    }
}

node* initRing(int *key_list, int length){
    if(length>1){
        int index = 1;
        node* begin_node = createNode(key_list[index-1],index);
        node* this_node = begin_node;
        for(index = 2;index<=length;index++){
            node* new_node = createNode(key_list[index-1],index);
            insertNode(this_node,new_node);
            this_node = new_node;
        }
        insertNode(this_node,begin_node);
        return begin_node;
    }else if(length==1){
        node* ret_node =  createNode(key_list[0],1);
        insertNode(ret_node,ret_node);
        return ret_node;
    }else{
        fprintf(stderr,"no key list no ring\n");
        return NULL;
    }
}

void simulate(node* first_node, int upper, ptr_node* path, int ret_index){

    if(first_node->_next==first_node){
        path[ret_index] = first_node;
        return;
    }
    node* end_node = first_node;
    for(int index=1;index<upper-1;index++){
        end_node = end_node->_next;
    }
    path[ret_index] = end_node->_next;
    upper = deleteNextNode(end_node);
    if(end_node->_next)  // Check for NULL
        simulate(end_node->_next, upper, path, ret_index+1);
    return ;
}

void printPath(ptr_node* path, int length){
    for(int i=0;i<length;i++){
        printf("The %d gays out is id=%d and key=%d\n",i+1,path[i]->_id,path[i]->_key);
    }
}

int main(void){
    ptr_node* path = (ptr_node*)malloc(7*sizeof(ptr_node));
    int keylist[7] = {3,1,7,2,4,8,4};
    node*first_node = initRing(keylist,7);
    simulate(first_node, 20,path,0);
    printPath(path,7);
    free(path);
    return 0;
}