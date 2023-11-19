#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_QUEEN 8

void backTrack(int n, int row, bool *cols, bool *diags1, bool *diags2, bool **this_state, bool ***res_states, int *res_index)
{
    if (row == n) {
        res_states[*res_index] = (bool **)malloc(n * sizeof(bool *));
        for (int i = 0; i < n; i++) {
            res_states[*res_index][i] = (bool *)malloc(n * sizeof(bool));
            for (int j = 0; j < n; j++) {
                res_states[*res_index][i][j] = this_state[i][j];
            }
        }
        (*res_index)++;
        return;
    }

    for (int col = 0; col < n; col++) {
        int diag1 = col - row + n - 1;
        int diag2 = col + row;
        if (!cols[col] && !diags1[diag1] && !diags2[diag2]) {
            this_state[row][col] = true;
            cols[col] = diags1[diag1] = diags2[diag2] = true;
            backTrack(n, row + 1, cols, diags1, diags2, this_state, res_states, res_index);
            this_state[row][col] = false;
            cols[col] = diags1[diag1] = diags2[diag2] = false;
        }
    }
    return;
}

bool **createBoard(int size)
{
    bool **board = (bool **)malloc(size * sizeof(bool *));
    for (int i = 0; i < size; i++) {
        board[i] = (bool *)malloc(size * sizeof(bool));
    }
    return board;
}

void printBoard(bool **board, int size)
{
    int i, j;

    printf("   ");
    for (i = 0; i < size; i++)
        printf("%d ", i);
    printf("\n");

    printf("   ");
    for (i = 0; i < size; i++)
        printf("--");
    printf("-\n");

    for (i = 0; i < size; i++) {
        printf("%d |", i);

        for (j = 0; j < size; j++) {
            printf("%c ", board[i][j] ? '#' : ' ');
        }

        printf("|\n");
    }

    printf("   ");
    for (i = 0; i < size; i++)
        printf("--");
    printf("-\n");
}

void eightQueens(void)
{
    bool **checkerboard = createBoard(NUM_QUEEN);

    bool *cols = (bool *)malloc(NUM_QUEEN * sizeof(bool));
    bool *diag1 = (bool *)malloc((2 * NUM_QUEEN - 1) * sizeof(bool));
    bool *diag2 = (bool *)malloc((2 * NUM_QUEEN - 1) * sizeof(bool));

    int ret_index = 0;
    bool ***res = (bool ***)malloc(sizeof(char **) * 10001);
    backTrack(NUM_QUEEN, 0, cols, diag1, diag2, checkerboard, res, &ret_index);
    for (int i = 0; i < ret_index; i++) {
        printBoard(res[i], NUM_QUEEN);
        printf("--------------------------\n");
    }
    printf("Total %d plans\n",ret_index);
    return;
}

int main(void)
{
    eightQueens();
    return 0;
}