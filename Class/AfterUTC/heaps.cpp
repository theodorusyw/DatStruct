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

    // upheap
    while(i != 0 && heap->arr[parent(i)] > heap->arr[i]) {
        swap(&heap->arr[parent(i)], &heap->arr[i]);
        i = parent(i);
    }
}

void downHeap(MinHeap* heap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if(left < heap->size && heap->arr[left] < heap->arr[i]) {
        smallest = left;
    }

    if(right < heap->size && heap->arr[right] < heap->arr[i]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        downHeap(heap, smallest);
    }
}

int extract(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Empty");
        return -1;
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    downHeap(heap, 0);
    return root;
}

int main() {
    MinHeap heap;
    heap.size = 0;

    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 5);
    printf("%d", heap.arr[0]);

    return 0;
}