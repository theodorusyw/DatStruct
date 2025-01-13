#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    char *valueNode;   // Nama Pokemon
    int ID;            // ID Pokemon
    int price;         // Harga Pokemon (100 Gold)
    struct tnode *next; // Pointer ke node berikutnya
} *h, *t;              // Pointer global untuk head dan tail

int count = 1; // Counter untuk ID Pokemon

void pushMid(char *poke) {
    struct tnode *c = (struct tnode*) malloc(sizeof(struct tnode)); // Alokasi memori untuk node baru
    c->valueNode = (char *)malloc(strlen(poke) + 1);               // Alokasi memori untuk nama Pokemon
    strcpy(c->valueNode, poke);                                    // Salin nama Pokemon
    c->next = NULL;                                                // Set next node ke NULL
    c->ID = count++;                                               // Set ID dan increment counter
    c->price = 100;                                                // Set harga Pokemon

    if (!h) {                  // Jika list kosong
        h = t = c;             // Node baru menjadi head dan tail
        return;
    }

    if (strcmp(poke, h->valueNode) < 0) { // Jika lebih kecil dari head
        c->next = h;                      // Node baru menunjuk ke head
        h = c;                            // Node baru menjadi head
        return;
    }

    if (strcmp(poke, t->valueNode) > 0) { // Jika lebih besar dari tail
        t->next = c;                      // Tail menunjuk ke node baru
        t = c;                            // Node baru menjadi tail
        return;
    }

    struct tnode *temp = h;               // Cari posisi yang tepat
    while (temp->next != NULL && strcmp(temp->next->valueNode, poke) < 0) {
        temp = temp->next;
    }
    c->next = temp->next;  // Node baru menunjuk ke node berikutnya
    temp->next = c;        // Node sebelumnya menunjuk ke node baru
}

void popMid(char *dicari, char *diganti) {
    if (!h) return; // Jika list kosong, keluar

    struct tnode *temp = h, *prev = NULL; // Pointer untuk traversal dan node sebelumnya

    while (temp != NULL && strcmp(dicari, temp->valueNode) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) { // Jika tidak ditemukan
        printf("Pokemon %s tidak ditemukan\n", dicari);
        return;
    }

    if (temp == h) h = temp->next;       // Jika node adalah head
    else prev->next = temp->next;        // Jika node bukan head
    if (temp == t) t = prev;             // Jika node adalah tail

    free(temp->valueNode); // Bebaskan memori
    free(temp);
    pushMid(diganti);      // Tambahkan Pokemon pengganti
}

void popMid2(char *input) {
    if (!h) return; // Jika list kosong, keluar

    struct tnode *temp = h, *prev = NULL; // Pointer untuk traversal dan node sebelumnya

    while (temp != NULL && strcmp(input, temp->valueNode) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) { // Jika tidak ditemukan
        printf("Pokemon %s tidak ditemukan\n", input);
        return;
    }

    if (temp == h) h = temp->next;       // Jika node adalah head
    else prev->next = temp->next;        // Jika node bukan head
    if (temp == t) t = prev;             // Jika node adalah tail

    free(temp->valueNode); // Bebaskan memori
    free(temp);
    printf("Pokemon %s berhasil dihapus!\n", input);
}

void printList() {
    struct tnode *temp = h; // Pointer untuk traversal
    while (temp != NULL) {
        puts("======================");
        printf("Name: %s\n", temp->valueNode); // Cetak nama
        printf("ID: %d\n", temp->ID);          // Cetak ID
        printf("Price: 100 Gold\n");           // Cetak harga
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
    int n, choice = -1;
    char *poke = (char*) malloc(sizeof(char));

    do {
        printMenu(); // Cetak menu utama
        printf(">> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Tambah Pokemon
                printf("Masukkan berapa pokemon yang anda punya: ");
                scanf("%d", &n);

                for (int i = 0; i < n; i++) {
                    printf("Masukkan Nama Pokemon %d: ", i + 1);
                    getchar();
                    scanf("%[^\n]", poke);
                    pushMid(poke); // Tambahkan Pokemon
                }

                printf("\nSetelah di Push Mid:\n");
                printList(); // Cetak list Pokemon
                break;
            }

            case 2: { // Tukar Pokemon
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

                    popMid(dicari, diganti); // Tukar Pokemon
                }

                printList(); // Cetak list Pokemon
                break;
            }

            case 3: { // Hapus Pokemon
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

                    popMid2(input); // Hapus Pokemon
                }

                printList(); // Cetak list Pokemon
                break;
            }

            case 4: {
                printf("Keluar dari program.\n");
                return 0; // Keluar program
            }
        }
    } while (choice >= 1 && choice <= 4);

    return 0;
}