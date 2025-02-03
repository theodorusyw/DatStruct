#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

typedef struct {
    char name[100];
    char phone[20];
    char email[20];
    struct Node* next;
} Node;

typedef struct {
    Node table[1000];
} HashTable;

int hashFunction(char* name) {
    int hash = 0;
    int key = 0;
    for (int i = 0; i < strlen(name); i++) {
        hash += name[i];
    }
    
    char temp[100];
    sprintf(temp, "%d", hash);

    if (strlen(temp) % 2 != 0) {
        char location[2] = {temp[strlen(temp)], '\0'};

        key = atoi(location);
        key += key;

        return key % max;
    } else {
        char location[3] = {temp[strlen(temp)], temp[strlen(temp)+1], '\0'};

        key = atoi(location);
        key += key;

        return key % max;
    }
}