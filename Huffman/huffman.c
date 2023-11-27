#include "huffman.h"

// Helper Functions 

Heap* createHeap() {
    Heap* h = (Heap*) malloc(sizeof(Heap));
    h->count = 0;
    return h;
}

void insertHeap(Heap* h, Node* node) {
    h->data[h->count] = node;
    h->count++;
}

Node* removeHeap(Heap* h) {
    int i, idx;
    Node* temp, *x;
    x = h->data[0];
    h->data[0] = h->data[h->count - 1];
    h->count--;
    temp = h->data[0];
    i = 0;

    // Heapify Down
    while (true) {
        idx = (i * 2) + 1;
        if ((idx < h->count) && (h->data[idx]->freq < temp->freq)) {
            if ((idx + 1 < h->count) && (h->data[idx + 1]->freq < h->data[idx]->freq)) {
                idx++;
            }
        } else if ((idx + 1 < h->count) && (h->data[idx + 1]->freq < temp->freq)) {
            idx++;
        } else {
            break;
        }
        h->data[i] = h->data[idx];
        i = idx;
    }
    h->data[i] = temp;
    return x;
}

void Huffman_Compress(FILE *input, FILE *output) {
    // TODO: Fill this function
    // You need to read the file, create a frequency array, create Huffman tree, and write the encoded data to the file 
}

void Huffman_Uncompress(FILE *input, FILE *output) {
    // TODO: Fill this function
    // You should read the file, read the Huffman Tree, and decode the data, then write it to the file
}
