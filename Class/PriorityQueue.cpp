#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int priorityQueue[MAX_SIZE];
int queueSize = 0;

void enqueue(int value) {
    if (queueSize == MAX_SIZE) {
        printf("Priority Queue Overflow, Cannot enqueue %d.\n");
        return;
    }

    int i = queueSize - 1;

    while (i >= 0 && priorityQueue[i] < value) {
        priorityQueue[i+1] = priorityQueue[i];
        i--;
    }

    priorityQueue[i+1] = value;
    queueSize++;

    printf("%d enqueued into the priority queue.\n", value);
}

int dequeue() {
    if (queueSize == 0) {
        printf("Priority Queue underflow, Cannot dequeue from an empty priority queue.\n");
        return -1;
    }

    int front = priorityQueue[queueSize-1];
    queueSize--;

    return front;
}

void display() {
    if (queueSize == 0) {
        printf("Priority Queue is empty.\n");
        return;
    }

    printf("Priority in the priority queue: ");
    for (int i = 0; i < queueSize; i++) {
        printf("%d ", priorityQueue[i]);
    }
    printf("\n");
}

int main() {
    
    return 0;
}