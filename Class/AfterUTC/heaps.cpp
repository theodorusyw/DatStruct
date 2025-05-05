#include <stdio.h>

#define MAX 100

typedef struct MinHeap {
    int size;
    int arr[MAX];
} MinHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) {
    return(i - 2) / 2;
}

int leftChild(int i) {
    return (i * 2 + 1);
}

int rightChild(int i) {
    return (i * 2 + 2);
}

void insert(MinHeap* heap, int value) {
    if (heap->size >= MAX) {
        printf("Full");
        return;
    }

    int i = heap->size;
    heap->arr[i] = value;
    heap->size++;

    while(i != 0 && heap->arr[parent(i)] > heap->arr[i]) {
        swap(&heap->arr[parent(i)], &heap->arr[i]);
    }
}

int main() {
    MinHeap heap;
    heap.size = 0;

    return 0;
}