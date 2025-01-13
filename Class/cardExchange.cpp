#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

struct tnode {
    char *nama; 
    int ID; 
    int price; 
    struct tnode *next; 
} *h, *t; 

int count = 1;

void pushMid (char *poke) {
    struct tnode *c = (struct tnode*)malloc(sizeof(struct tnode));
    c->nama = (char*)malloc(strlen(poke)+1);
    strcpy(c->nama, poke);
    c->next = NULL;
    c->ID = count++;
    c->price = 100;

    if (!h) {
        h = t = c;
        return;
    }

    if (strcmp(poke, h->nama)<0) {
        c->next = h;
        h = c;
        return;
    }

    if (strcmp(poke, t->nama)>0) {
        t->next = c;
        t = c;
        return;
    }

    struct tnode* temp = h;
    while (temp->next != NULL && strcmp(temp->next->nama, poke)<0) {
        temp = temp->next;
    }
    c->next = temp->next;
    temp->next = c;
}

void popMid(char* dicari, char* diganti) {
    if (!h) return;

    struct tnode *temp = h, *prev = NULL;

    while (temp != NULL && strcmp(dicari, temp->nama)!=0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Pokemon %s tidak ditemukan\n", dicari);
        return;
    }

    if (temp == h) h = temp->next;
    else prev->next == temp->next;
    if (temp == t) t = prev;

    free(temp->nama);
    free(temp);
    pushMid(diganti);
}

void popMid2(char* input) {
    if (!h) return;

    struct tnode *temp = h, *prev = NULL;

    while (temp != NULL && strcmp(input, temp->nama)!=0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Pokemon %s tidak ditemukan\n", input);
        return;
    }

    if (temp == h) h = temp->next;
    else prev->next == temp->next;
    if (temp == t) t = prev;

    free(temp->nama);
    free(temp);
    printf("Pokemon %s berhasil dihapus\n", input);
}

void printList() {
    struct tnode *temp = h;
    while (temp != NULL) {
        puts("=========================");
        printf("Name: %s\n", temp->nama);
        printf("ID: %d\n", temp->ID);
        printf("Price: 100 Gold\n");
        temp = temp->next;
    }
    puts("=========================");
    puts("NULL");
    puts("=========================");
}

int main() {
    int n;
    char *poke = NULL;

    // Input Pokemon
    printf("Masukkan berapa pokemon yang anda punya: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Masukkan Nama Pokemon %d: ", i+1);
        poke = (char*)malloc(100 * sizeof(char)); gc
        scanf("%[^\n]", poke);
        pushMid(poke);
    }

    printList();

    // Menuker Nidoran sama Charmander
    char *dicari = (char*)malloc(sizeof(char));
    char *diganti = (char*)malloc(sizeof(char));

    printf("Masukkan pokemon yang ingin ditukar: ");
    scanf("%s", dicari); gc
    
    printf("Masukkan pokemon yang ingin diganti: ");
    scanf("%s", diganti); gc

    popMid(dicari, diganti);

    printList();

    puts("===========================================");

    // Beli Pikachu
    char *nama = (char*)malloc(sizeof(char));
    printf("Masukkan nama pokemon yang diincar: ");
    scanf("%s", nama); gc
    pushMid(nama);

    printList();

    puts("===========================================");

    // Jual Zubat
    char *jual = (char*)malloc(sizeof(char));
    printf("Masukkan nama pokemon yang ingin dijual: ");
    scanf("%s", jual); gc
    popMid2(jual);

    printList();

    puts("===========================================");
}