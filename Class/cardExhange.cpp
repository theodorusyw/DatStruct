#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    char *valueNode; // Menyimpan nama pokemon
    int ID; // Menyimpan ID pokemon
    int price; // Menyimpan harga pokemon
    struct tnode *next; // Pointer ke node berikutnya
} *h, *t;

int count = 1;

void pushMid(char *poke) {
    struct tnode *c = (struct tnode*) malloc(sizeof(struct tnode));
    c->valueNode = (char *)malloc(strlen(poke) + 1);
    strcpy(c->valueNode, poke);
    c->next = NULL;
    c->ID = count++;
    c->price = 100;

    if (!h) {
        h = t = c;
        return;
    }

    if (strcmp(poke, h->valueNode) < 0) {
        c->next = h;
        h = c;
        return;
    }

    if (strcmp(poke, t->valueNode) > 0) {
        t->next = c;
        t = c;
        return;
    }

    struct tnode *temp = h;
    while (temp->next != NULL && strcmp(temp->next->valueNode, poke) < 0) {
        temp = temp->next;
    }
    c->next = temp->next;
    temp->next = c;
}

void popMid(char *dicari, char *diganti) {
    if (!h) return;

    struct tnode *temp = h;
    struct tnode *prev = NULL;

    while (temp != NULL && strcmp(dicari, temp->valueNode) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Pokemon %s tidak ditemukan\n", dicari);
        return;
    }

    if (temp == h) {
        h = temp->next;
    } else {
        prev->next = temp->next;
        if (temp == t) t = prev;
    }

    free(temp->valueNode);
    free(temp);

    pushMid(diganti);
}

void popMid2(char *input) {
    if (!h) return;

    struct tnode *temp = h;
    struct tnode *prev = NULL;

    while (temp != NULL && strcmp(input, temp->valueNode) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Pokemon %s tidak ditemukan\n", input);
        return;
    }

    if (temp == h) {
        h = temp->next;
    } else {
        prev->next = temp->next;
        if (temp == t) t = prev;
    }

    free(temp->valueNode);
    free(temp);

    printf("Pokemon %s berhasil dihapus!\n", input);
}

void printList() {
    struct tnode *temp = h;
    while (temp != NULL) {
        puts("======================");
        printf("Name: %s\n", temp->valueNode);
        printf("ID: %d\n", temp->ID);
        printf("Price: 100 Gold\n");
        temp = temp->next;
    }
    puts("======================");
    printf("NULL\n");
    puts("======================");
}

void printMenu() {
    puts("1. Add Pokemon");
    puts("2. Change Pokemon");
    puts("3. Delete Pokemon");
    puts("4. Exit");
}

int main() {
    int n;
    char *poke = (char*) malloc(sizeof(char));

    int choice = -1;

    do {
        printMenu();
        printf(">> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // INPUT POKEMON
                printf("Masukkan berapa pokemon yang anda punya: ");
                scanf("%d", &n);

                for (int i = 0; i < n; i++) {
                    printf("Masukkan Nama Pokemon %d: ", i + 1);
                    getchar();
                    scanf("%[^\n]", poke);
                    pushMid(poke);
                }

                printf("\nSetelah di Push Mid:\n");
                printList();
                break;
            }

            case 2: {
                // TUKAR POKEMON
                int k;
                do {
                    printf("Masukkan berapa kali anda ingin menukar [maks %d]: ", n);
                    scanf("%d", &k);
                } while (k < 1 || k > n);

                for (int i = 0; i < k; i++) {
                    char dicari[100], diganti[100];

                    printf("Masukkan pokemon yang ditukar: ");
                    getchar();
                    scanf("%[^\n]", dicari);

                    printf("Masukkan pokemon pengganti: ");
                    getchar();
                    scanf("%[^\n]", diganti);

                    popMid(dicari, diganti);
                }

                printList();
                break;
            }

            case 3: {
                // HAPUS POKEMON
                int k;
                do {
                    printf("Masukkan berapa kali anda ingin menghapus [maks %d]: ", n);
                    scanf("%d", &k);
                } while (k < 1 || k > n);

                for (int i = 0; i < k; i++) {
                    char input[100];

                    printf("Masukkan pokemon yang ingin dihapus: ");
                    getchar();
                    scanf("%[^\n]", input);

                    popMid2(input);
                }

                printList();
                break;
            }

            case 4: {
                printf("Keluar dari program.\n");
                return 0;
            }
        }
    } while (choice >= 1 && choice <= 4);

    return 0;
}