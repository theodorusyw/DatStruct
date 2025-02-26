#include <stdio.h>
#include <stdlib.h>

#define VM_COUNT 10

typedef struct Vulnerability {
    int id;
    int severity;
    struct Vulnerability* next;
} Vulnerability;

Vulnerability* head = NULL;

void printQueue();

// iki dinggo nentuke tinkat keparahan berdasarkan impact karo likelihood
int determineSeverity(int impact, int likelihood) {
    if (impact == 1 && likelihood == 1) return 3; // iki Critical
    if (impact == 1 && likelihood == 0) return 2; // iki High
    if (impact == 0 && likelihood == 1) return 1; // iki Medium
    return 0; // iki Low
}

void enqueue(int id, int impact, int likelihood) {
    int severity = determineSeverity(impact, likelihood);
    
    Vulnerability* newNode = (Vulnerability*)malloc(sizeof(Vulnerability));
    newNode->id = id;
    newNode->severity = severity;
    newNode->next = NULL;

    if (head == NULL || severity > head->severity) {
        newNode->next = head;
        head = newNode;
    } else {
        Vulnerability* temp = head;
        while (temp->next != NULL && temp->next->severity >= severity) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// iki dinggo golek sek terparah nng antrian
int findHighestSeverity() {
    Vulnerability* temp = head;
    int maxSeverity = -1;
    while (temp != NULL) {
        if (temp->severity > maxSeverity) {
            maxSeverity = temp->severity;
        }
        temp = temp->next;
    }
    return maxSeverity;
}

void dequeue() {
    if (head == NULL) return;

    int highestSeverity = findHighestSeverity();
    if (highestSeverity == -1) return;

    Vulnerability* temp = head;
    Vulnerability* prev = NULL;

    printf("\nProcessing vulnerabilities...\n\n");
    printf("Stored Processed Vulnerabilities:\n");

    while (temp != NULL) {
        if (temp->severity == highestSeverity) { 
            int vmIndex = temp->id % VM_COUNT;
            printf("VM %d -> ID: %d\n", vmIndex, temp->id);

            if (prev == NULL) {
                head = temp->next;
                free(temp);
                temp = head;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    printQueue();
}

void printQueue() {
    Vulnerability* temp = head;
    printf("\nVulnerability Queue:\n");
    while (temp != NULL) {
        const char* severityStr;
        switch (temp->severity) {
            case 3: severityStr = "Critical"; break;
            case 2: severityStr = "High"; break;
            case 1: severityStr = "Medium"; break;
            default: severityStr = "Low";
        }
        printf("ID: %d - %s\n", temp->id, severityStr);
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

    return 0;
}
