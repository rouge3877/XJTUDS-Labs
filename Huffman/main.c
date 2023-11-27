#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: huff -[c|d] infile outfile\n");
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(argv[2], "rb");
    if (!in) {
        perror("Unable to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(argv[3], "wb");
    if (!out) {
        perror("Unable to open output file");
        exit(EXIT_FAILURE);
    }

    if (argv[1][0] == '-' && argv[1][1] == 'c') {
        Huffman_Compress(in, out);
    } else if (argv[1][0] == '-' && argv[1][1] == 'd') {
        Huffman_Uncompress(in, out);
    } else {
        fprintf(stderr, "Unknown command\n");
        exit(EXIT_FAILURE);
    }

    fclose(in);
    fclose(out);
  
    return 0;
}
