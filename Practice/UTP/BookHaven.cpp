#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100
#define gc getchar();
#define clear system("clear");

typedef struct Node {
    char borrowID[6];
    char name[35];
    char libraryID[10];
    char title[55];
    int duration;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

void enterToContinue() {
    puts("Press ENTER To Continue..."); gc
}

int generateKey(int n) {
    int squared = n * n;
    int middle = (squared / 100) % 100;
    return squared % TABLE_SIZE;
}

char* generateBorrowID(const char* title) {
    char* borrowID = (char*)malloc(6 * sizeof(char));
    snprintf(borrowID, sizeof(borrowID), "%c%c%03d", toupper(title[0]), toupper(title[1]), rand() % 1000);
    return borrowID;
}

bool validName(const char* name) {
    return strlen(name) <= 30 && strlen(name) >= 3;
}

bool validLibraryID(const char* libraryID) {
    return strlen(libraryID) == 9 && strncmp(libraryID, "LIB-", 4) == 0;
}

bool validTitle(const char* title) {
    return strlen(title) <= 50 && strlen(title) >= 3;
}

bool validDuration(int duration) {
    return duration >= 1 && duration <= 30;
}

void borrowBook() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        puts("Memory allocation failed");
        return;
    }

    do {
        printf("Enter your full name: ");
        scanf("%[^\n]", newNode->name); gc
    } while (!validName(newNode->name));
    
    do {
        printf("Enter your library ID (format: LIB-xxxxx): ");
        scanf("%s", newNode->libraryID); gc
    } while (!validLibraryID(newNode->libraryID));

    do {
        printf("Enter the book title: ");
        scanf("%[^\n]", newNode->title); gc
    } while (!validTitle(newNode->title));

    do {
        printf("Enter borrowing duration (1-30 days): ");
        scanf("%d", &newNode->duration); gc
    } while (!validDuration(newNode->duration));

    strcpy(newNode->borrowID, generateBorrowID(newNode->title));
    int key = generateKey(atoi(newNode->borrowID + 2));
    
    newNode->next = hashTable[key];
    hashTable[key] = newNode;

    puts("--------------------------------------");
    puts("✅ Book borrowed successfully ✅");
    puts("--------------------------------------");
    printf("Borrowing ID  : %s\n", newNode->borrowID);
    printf("Borrower Name : %s\n", newNode->name);
    printf("Library ID    : %s\n", newNode->libraryID);
    printf("Book Title    : %s\n", newNode->title);
    printf("Duration      : %d\n", newNode->duration);
    puts("--------------------------------------");

    enterToContinue();
}

void viewBorrowedBooks() {
    int found = 0;
    puts("======================================");
    puts("Borrowed Books List");
    puts("======================================");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            printf("Borrowing ID  : %s\n", current->borrowID);
            printf("Borrower Name : %s\n", current->name);
            printf("Library ID    : %s\n", current->libraryID);
            printf("Book Title    : %s\n", current->title);
            printf("Duration      : %d\n", current->duration);
            puts("--------------------------------------");
            current = current->next;
            found = 1;
        }
    }
    if (!found) {
        puts("--------------------------------------");
        puts("No books borrowed yet.");
        puts("--------------------------------------");
    }
    enterToContinue();
}

void returnBook() {
    viewBorrowedBooks();

    char id[6];

    printf("Enter Borrowing ID: ");
    scanf("%s", id); gc

    int key = generateKey(atoi(id + 2));
    Node *temp = hashTable[key], *prev = NULL;

    while (temp && strcmp(temp->borrowID, id) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        puts("--------------------------------------");
        puts("Borrowing ID not found.");
        puts("--------------------------------------");
        enterToContinue();
        return;
    }

    if (prev)
        prev->next = temp->next;
    else
        hashTable[key] = temp->next;
    
    free(temp);
    puts("--------------------------------------");
    puts("✅ Book returned successfully! ✅");
    puts("--------------------------------------");
    enterToContinue();
}

void printMenu() {
    clear
    puts("======================================");
    puts("📚📚 BookHaven Library Management 📚📚");
    puts("======================================");
    puts("1. Borrow a Book");
    puts("2. View Borrowed Books");
    puts("3. Return a Book");
    puts("4. Exit");
    puts("======================================");
}

int main () {
    int choice = 0;
    do {
        printMenu();
        do {
            printf("Enter your choice: ");
            scanf("%d", &choice); getchar();
        } while (choice < 1 || choice > 4);

        switch (choice) {
            case 1: borrowBook(); break;
            case 2: viewBorrowedBooks(); break;
            case 3: returnBook(); break;
            case 4:
            puts("Thank you for using BookHaven Library Management!!!");
            enterToContinue();
            break;
        }
    } while (choice != 4);
    return 0;
}