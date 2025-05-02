#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Jumlah vertex = 5
#define MAX 5

void createMatrix(int matrix[][MAX], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(int matrix[][MAX], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int vertices = MAX;

    int matrix[MAX][MAX];
    createMatrix(matrix, vertices);

    return 0;
}