#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Struktur data untuk contact person
typedef struct Contact {
    char name[50];
    char phone[20];
    char email[50];
    struct Contact* next;
} Contact;

// Hash table
Contact* hashTable[TABLE_SIZE];

// Algoritma hash unik (kombinasi XOR dan modulus)
int uniqueHashFunction(char* name) {
    unsigned int hash = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        hash = (hash ^ name[i]) * 16777619;
    }
    return hash % TABLE_SIZE;
}

// Fungsi untuk menambahkan contact person
void insertContact(char* name, char* phone, char* email) {
    int index = uniqueHashFunction(name);
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    newContact->next = NULL;
    
    if (hashTable[index] == NULL) {
        hashTable[index] = newContact;
    } else {
        Contact* temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newContact;
    }
}

// Fungsi untuk mencari contact person
Contact* searchContact(char* name) {
    int index = uniqueHashFunction(name);
    Contact* temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Fungsi untuk menghapus contact person
void deleteContact(char* name) {
    int index = uniqueHashFunction(name);
    Contact* temp = hashTable[index];
    Contact* prev = NULL;
    
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Contact not found!\n");
        return;
    }
    
    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Contact deleted successfully!\n");
}

// Fungsi untuk menampilkan seluruh contact person dan jumlah collision
void displayContacts() {
    int collisionCount = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Contact* temp = hashTable[i];
        int count = 0;
        while (temp != NULL) {
            printf("[%s, %s, %s] -> ", temp->name, temp->phone, temp->email);
            temp = temp->next;
            count++;
        }
        if (count > 1) {
            collisionCount += (count - 1);
        }
        printf("NULL\n");
    }
    printf("Total Collisions: %d\n", collisionCount);
}

// Fungsi utama
int main() {
    insertContact("Alice", "123456789", "alice@example.com");
    insertContact("Bob", "987654321", "bob@example.com");
    insertContact("Charlie", "555123456", "charlie@example.com");
    insertContact("Dave", "111222333", "dave@example.com");
    insertContact("Eve", "444555666", "eve@example.com");
    insertContact("Frank", "777888999", "frank@example.com");
    
    displayContacts();
    
    Contact* found = searchContact("Alice");
    if (found) {
        printf("\nContact Found: %s, %s, %s\n", found->name, found->phone, found->email);
    } else {
        printf("\nContact Not Found\n");
    }
    
    deleteContact("Bob");
    displayContacts();
    
    return 0;
}