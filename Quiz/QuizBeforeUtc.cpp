#include <stdio.h>
#include <stdlib.h>

#define VM_COUNT 10
#define MAX_SIZE 10

struct Vulnerability {
    int id;
    int severity; // nek 3 ki Critical, nek 2 ki High, nek 1 ki Medium, nek 0 ki Low
    struct Vulnerability* next;
};

Vulnerability *head = NULL;

int hashFuction(int id) {
    return id % VM_COUNT;
}

int determineSeverity(int impact, int likelihood) {
    if (impact == 1 && likelihood == 1) return 3;
    if (impact == 1 && likelihood == 0) return 2;
    if (impact == 0 && likelihood == 1) return 1;
    return 0;
}

void enqueue(int id, int impact, int likelihood) {
    int severity = determineSeverity(impact, likelihood);

    Vulnerability *newNode = (Vulnerability*)malloc(sizeof(Vulnerability));
    newNode->id = id;
    newNode->severity = severity;
    newNode->next = NULL;

    if (head == NULL || severity > head->severity) {
        newNode->next = head;
        head = newNode;
    } else {
        Vulnerability *temp = head;
        while (temp->next != NULL && temp->next->severity >= severity) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void dequeue() {
    if (head == NULL) return;

    Vulnerability *temp = head;
    head = head->next;

    int index = temp->id % VM_COUNT;

    printf("Processing vulnerabilities...\n");

    free(temp);
}

void printQueue() {
    Vulnerability *temp = head;
    printf("\nVulnerability Queue:\n");
    while (temp != NULL) {
        printf("ID: %d - %d\n", temp->id, temp->severity);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    enqueue(3001, 0, 0);
    enqueue(3002, 1, 1);
    enqueue(3003, 1, 0);
    enqueue(3004, 0, 1);
    enqueue(3005, 1, 1);

    printQueue();
    
    dequeue();
    printQueue();
    
    dequeue();
    printQueue();

    return 0; 
}