#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Visitor {
    char nama[50];
    char tiket[15];
    struct Visitor *prev;
    struct Visitor *next;
} Visitor;

Visitor *head = NULL;
Visitor *tail = NULL;

Visitor *createVisitor(char *nama, char *tiket) {
    Visitor* newVisitor = (Visitor*)malloc(sizeof(Visitor));
    strcpy(newVisitor->nama, nama);
    strcpy(newVisitor->tiket, tiket);
    newVisitor->prev = newVisitor->next = NULL;
    return newVisitor;
}

void registerVisitor(char *nama, char *tiket) {
    Visitor *newVisitor = createVisitor(nama, tiket);

    // kalo antriannya kosong
    if (!head) {
        head = tail = newVisitor;
        return;
    }

    Visitor *current = head;
    
    // memprioritaskan FAST_TRACK di depan REGULER
    while(current && strcmp(current->tiket, "FAST_TRACK") == 0) {
        current = current->next;
    }

    // masukin setelah FAST_TRACK
    if (current) {
        newVisitor->next = current;
        newVisitor->prev = current->prev;
        if (current->prev) current->prev->next = newVisitor;
        else head = newVisitor;
        current->prev = newVisitor;
    } else { // kalo ngga ada REGULER dimasukin di belakang
        tail->next = newVisitor;
        newVisitor->prev = tail;
        tail = newVisitor;
    }
}

void removeVisitor(char *nama) {
    Visitor *current = head;

    while (current) {
        // hapus node
        if (strcmp(current->nama, nama) == 0) {
            if (current->prev) current->prev->next = current->next;
            else head = current->next;

            if (current->next) current->next->prev = current->prev;
            else tail = current->prev;

            free(current);
            return;
        }
        current = current->next;
    }
}

void callVisitor() {
    Visitor *current = head;
    int count = 0;

    printf("\n");
    // masukan 4 visitor
    while (current && count < 4) {
        printf("%s ", current->nama);
        Visitor *toDel = current;
        current = current->next;
        removeVisitor(toDel->nama);
        count++;
    }

    printf("got into the boat.\n");

    // hitung sisa visitor
    int remain = 0;
    current = head;
    while (current) {
        remain++;
        current = current->next;
    }

    printf("%d queues remaining.\n\n", remain);
}

void displayQueue() {
    printf("\nNo  Name\t\tTicket\n");
    Visitor *current = head;
    int index = 1;
    while (current) {
        printf("%d   %s \t\t%s\n", index++, current->nama, current->tiket);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int n;
    char nama[50];
    char tiket[15];
    char command[10];

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "REGISTER") == 0) {
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                scanf("%s %s", nama, tiket);
                registerVisitor(nama, tiket);
            }
            displayQueue();
        } else if (strcmp(command, "REMOVE") == 0) {
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                scanf("%s", nama);
                removeVisitor(nama);
            }
            displayQueue();
        } else if (strcmp(command, "CALL") == 0) {
            callVisitor();
        }
    }

    return 0;
}   