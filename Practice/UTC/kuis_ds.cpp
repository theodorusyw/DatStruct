#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

typedef struct Node {
    char id[7];
    char address[21];
    char type[10];
    struct Node *next;
} Node;

Node *head = NULL;

void generateID(char id[]) {
    id[0] = 'C'; id[1] = 'P'; id[2] = 'X';
    for (int i = 3; i < 6; i++) {
        id[i] = (rand() % 36 < 10) ? (rand() % 10 + '0') : (rand() % 26 + 'A');
    }
    id[6] = '\0';
}

void printMenu() {
    puts("Copi Xpress");
    puts("1. Insert new package");
    puts("2. Send a package");
    puts("3. View all package");
    puts("4. Exit");
}

bool validAddress(char address[]) {
    return (strlen(address) <= 20 && strlen(address) >= 5 && strncmp(address, "JL. ", 4) == 0);
}

bool validType(char type[]) {
    return (strcmp(type, "Economy") == 0 || strcmp(type, "Standard") == 0 || strcmp(type, "Instant") == 0);
}

void insertPackage() {
    Node* newNode = (Node*)malloc(sizeof(Node));

    do {
        printf("Address (must start with \"JL. \", 5-20 characters): ");
        scanf("%[^\n]", newNode->address); gc
    } while(!validAddress(newNode->address));

    do {
        printf("Package Type (Economy/Standard/Instant): ");
        scanf("%[^\n]", newNode->type); gc
    } while(!validType(newNode->type));

    generateID(newNode->id);
    newNode->next = NULL;

    if (!head || strcmp(newNode->type, "Instant") == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node *temp = head, *prev = NULL;
        while (temp && strcmp(temp->type, "Instant") == 0) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp || strcmp(newNode->type, "Standard") == 0) {
            newNode->next = temp;
            if (prev) prev->next = newNode;
            else head = newNode;
        } else {
            while (temp && strcmp(temp->type, "Economy") == 0) {
                prev = temp;
                temp = temp->next;
            }
            newNode->next = temp;
            prev->next = newNode;
        }
    }

    printf("Package inserted: %s (%s) -> %s\n", newNode->id, newNode->type, newNode->address);
}

void sendPackage() {

}

void viewPackage() {

}

void enterToContinue() {
    printf("Enter To Continue..."); gc
}

int main() {
    int choice = 0;
    do {
        printMenu();
        do {
            printf(">> ");
            scanf("%d", &choice); gc
        } while(choice < 1 && choice > 4);

        switch (choice) {
            case 1: insertPackage(); break;
            case 2: sendPackage(); break;
            case 3: viewPackage(); break;
            case 4: return 0;
        }
    } while(1);

    return 0;
}