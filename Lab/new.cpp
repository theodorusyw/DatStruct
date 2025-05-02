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

void addEdgeMatrix(int matrix[][MAX], int src, int dst) {
    matrix[src][dst] = 1; // kalau punya jalur -> kita tandain 1
    matrix[dst][src] = 1; // karena undirected -> kalo A bisa ke B, B juga bisa ke A
}

void bfsMatrix(int matrix[][MAX], int vertices, int startVertex) {
    // Step 1: Initialize Visited Array
    bool visited[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    // Step 2: Create Queue
    int queue[100];
    int front = 0;
    int rear = 0;

    visited[startVertex] = true; // kita tandain visited
    queue[rear++] = startVertex; // kita masukin ke queue

    // Kita pengen Looping untuk BFS
    while (front < rear) {
        int currentVertex = queue[front++]; 
        printf("%d ", currentVertex);

        // Kita pengen explore vertex tersebut punya nneighbor
        for (int i = 0; i < vertices; i++) {
            // untuk cek apakah ada edge         // biar ga visit node yang udah pernah
            if (matrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true; // kita tandain true karena udah ke visit
                queue[rear++] = i; // kita masukin ke queue
            }
        }
    }
}

void dfsMatrix(int matrix[][MAX], int vertices, int startVertex) {
    // Step 1: Initialize Visited Array
    bool visited[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    
    int stack[100], top = -1;
    stack[++top] = startVertex; // Karena top nya di index 0
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
    printMatrix(matrix, vertices);

    addEdgeMatrix(matrix, 0, 1);
    addEdgeMatrix(matrix, 0, 2);
    addEdgeMatrix(matrix, 1, 2);
    addEdgeMatrix(matrix, 1, 3);
    addEdgeMatrix(matrix, 2, 4);

    puts("Adjacency Matrix:");
    printMatrix(matrix, vertices);

    puts("BFS Traversal:");

    return 0;
}