#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 50

struct Spacecraft{
    char spacecraftName[101];
    int fuelLevel;
    int emergencyStatus;
    struct Spacecraft *next;
} *head;

void enqueue(char *spacecraftName, int fuelLevel, int emergencyStatus){
    struct Spacecraft *newNode = (Spacecraft*)malloc(sizeof(Spacecraft));
    strcpy(newNode->spacecraftName, spacecraftName);
    newNode->fuelLevel = fuelLevel;
    newNode->emergencyStatus = emergencyStatus;

    if(head == NULL || emergencyStatus > head->emergencyStatus || (emergencyStatus == head->emergencyStatus && fuelLevel < head->fuelLevel)){
        newNode->next = head;
        head = newNode;
    } else {
        struct Spacecraft *temp = head;
        while(temp->next != NULL && (temp->next->emergencyStatus > emergencyStatus || (temp->next->emergencyStatus == emergencyStatus && temp->next->fuelLevel <= fuelLevel))){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void dequeue(){
    struct Spacecraft *temp = head;
    if(head == NULL) return;
    head = head->next;
    free(temp);
}

void printQueue(){
    struct Spacecraft *temp = head;
    if(head == NULL) return;
    while(temp != NULL){
        printf("%s -> ", temp->spacecraftName);
        temp = temp->next;
    }
    puts("NULL");
}

int main(){
    enqueue("Apollo", 75, 0);
    enqueue("Voyager", 50, 0);
    enqueue("Odyssey", 90, 1);
    enqueue("Endeavour", 15, 0);
    enqueue("Pioneer", 80, 1);
    printQueue();
    dequeue();
    printQueue();
    return 0;
}