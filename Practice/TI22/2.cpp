#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

struct Spacecraft {
    char name[50];
    int fuelLevel;
    int emergency;
    struct Spacecraft* next;
} *head;

void enqueue(char *name, int fuelLevel, int emergency) {
    struct Spacecraft *newNode = (Spacecraft*)malloc(sizeof(Spacecraft));
    strcpy(newNode->name, name);
    newNode->fuelLevel = fuelLevel;
    newNode->emergency = emergency;

    if (head == NULL || emergency > head->emergency || (emergency == head->emergency && fuelLevel < head->fuelLevel)) {
        newNode->next = head;
        head = newNode;
    } else {
        struct Spacecraft *temp = head;
        while(temp->next != NULL && (temp->next->emergency > emergency || (temp->next->emergency == emergency && temp->next->fuelLevel <= fuelLevel))) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void dequeue() {
    struct Spacecraft *temp = head;
    head = head->next;
    free(temp);
}

void printQueue() {
    struct Spacecraft *temp = head;
    if(head == NULL) return;
    while(temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    puts("NULL");
}

int main() {
    enqueue("Apollo", 75, 0);
    enqueue("Voyager", 50, 0);
    enqueue("Odyssey", 90, 1);
    enqueue("Endeavour", 15,0);
    enqueue("Pioneer", 80, 1);
    printQueue();
    dequeue();
    printQueue();
    return 0;
}