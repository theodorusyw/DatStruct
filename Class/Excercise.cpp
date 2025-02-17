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

    if (!head) {
        head = tail = newVisitor;
        return;
    }

    if (strcmp(newVisitor->tiket, "FAST_TRACK") == 0) {
        Visitor *current = head;
        while (current && strcmp(current->tiket, "FAST_TRACK") == 0) {
            current = current->next;
        }

        // nek ono REGULER, lebokke sakdurunge REGULER pertama
        if (current) {
            newVisitor->next = current;
            newVisitor->prev = current->prev;
            if (current->prev) {
                current->prev->next = newVisitor;
            } else {
                head = newVisitor;
            }
            current->prev = newVisitor;
        } else { 
            // nek ra ono REGULER, ditambahno neng mburine
            tail->next = newVisitor;
            newVisitor->prev = tail;
            tail = newVisitor;
        }
    } else { 
        Visitor *current = tail;
        while (current && strcmp(current->tiket, "REGULER") != 0) {
            current = current->prev;
        }

        // nek ono REGULER, lebokke sak bar e REGULER terakhir
        if (current) {
            newVisitor->next = current->next;
            if (current->next) {
                current->next->prev = newVisitor;
            } else {
                tail = newVisitor;
            }
            current->next = newVisitor;
            newVisitor->prev = current;
        } else { 
            // nek rung ono REGULER, ditambahno neng mburi
            tail->next = newVisitor;
            newVisitor->prev = tail;
            tail = newVisitor;
        }
    }
}


void removeVisitor(char *nama) {
    Visitor *current = head;

    while (current) {
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

    // njeluk 4 visitor pertama
    while (current && count < 4) {
        printf("%s ", current->nama);
        Visitor *toDel = current;
        current = current->next;
        removeVisitor(toDel->nama);
        count++;
    }

    printf("got into the boat.\n");

    // itung sisane visitor
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