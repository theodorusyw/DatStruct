#include <stdio.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int heapSize = 0;

int left(int n) {
    return n * 2 + 1;
}

int right(int n) {
    return n * 2 + 2;
}

int parent(int n) {
    return (n - 1) / 2;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertHeap(int val) {
    if (heapSize == MAX_HEAP_SIZE) {
        printf("Heap penuh\n");
        return;
    }
    
    int n = heapSize++;

    heap[n] = val;

    while (n != 0 && heap[parent(n)] < heap[n]) {
        swap(&heap[parent(n)], &heap[n]);
        n = parent(n);
    }
}

void printHeapArray() {
    for (int i = 0; i < heapSize; i++) {
        printf("%d ->", heap[i]);
    }
    printf("\n");
}

int main() {
    insertHeap(9);
    printHeapArray();
    insertHeap(19);
    printHeapArray();
    insertHeap(36);
    printHeapArray();
    insertHeap(8);
    printHeapArray();
    insertHeap(10);
    printHeapArray();
    insertHeap(12);
    printHeapArray();

    return 0;
}