#include <stdio.h>
#include <stdlib.h>

/* Creating Huffman tree node */
typedef struct Node {
	char data;
	unsigned freq;
	struct Node *left, *right;
} Node;

Node* newNode(char data, unsigned freq) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->freq = freq;
	node->left = node->right = NULL;
	return node;
}

/* Creating priority queue */
typedef struct PriorityQueue {
	unsigned size;
	unsigned capacity;
	Node **array;
} PriorityQueue;

PriorityQueue* createPriorityQueue(unsigned capacity) {
	PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->size = 0;
	pq->capacity = capacity;
	pq->array = (Node**)malloc(pq->capacity * sizeof(Node*));
	return pq;
}

void swapNode(Node** a, Node** b) {
	Node* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(PriorityQueue* pq, int idx) {
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	if (left < pq->size && pq->array[left]->freq < pq->array[smallest]->freq)
		smallest = left;
	if (right < pq->size && pq->array[right]->freq < pq->array[smallest]->freq)
		smallest = right;
	if (smallest != idx) {
		swapNode(&pq->array[smallest], &pq->array[idx]);
		minHeapify(pq, smallest);
	}
}

Node* extractMin(PriorityQueue* pq) {
	Node* temp = pq->array[0];
	pq->array[0] = pq->array[pq->size - 1];
	--pq->size;
	minHeapify(pq, 0);
	return temp;
}

/* Utility function to check if size of heap is 1 or not. */
int isSizeOne(PriorityQueue* minHeap) {
	return (minHeap->size == 1);
}


/* A utility function to create a min heap of capacity is equal to size
   and inserts all character of data[] in min heap.
   Initially size of min heap is equal to capacity */
   PriorityQueue* createAndBuildMinHeap(char data[], int freq[], int size) {
    PriorityQueue* minHeap = createPriorityQueue(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

Node* buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;

    PriorityQueue* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(Node* root) {
    return !(root->left) && !(root->right);
}

void printCodesInternal(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodesInternal(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodesInternal(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArray(arr, top);
    }
}

void printCodes(Node* root) {
    int arr[MAX_TREE_HT], top = 0;
    printCodesInternal(root, arr, top);
}

void HuffmanCodes(char data[], int freq[], int size) {
    Node* root = buildHuffmanTree(data, freq, size);
    printCodes(root);
}