#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TABLE_SIZE 100

typedef struct Vehicle {
    char plate[12];
    char type[10];
    char parkID[6];
    struct Vehicle* next;
} Vehicle;

Vehicle* hashTable[TABLE_SIZE];

void enterToContinue() {
    printf("Tekan ENTER untuk melanjutkan...");
    getchar();
}

int hashFunction(char* parkID) {
    int len = strlen(parkID);
    int key = (parkID[len - 3] - '0') * 100 + (parkID[len - 2] - '0') * 10 + (parkID[len - 1] - '0');
    return key % TABLE_SIZE;
}

char* generateParkID(char* plate) {
    static char parkID[6];
    int randomNum = (rand() % 900) + 100; 
    snprintf(parkID, sizeof(parkID), "%.2s%d", plate, randomNum);
    for (int i = 0; i < 2; i++) parkID[i] = toupper(parkID[i]);
    return parkID;
}

void addVehicle() {
    char plate[12], type[10];
    
    printf("Masukkan nomor plat kendaraan (XX 1234 YY): ");
    scanf(" %[^\n]", plate); getchar(); // consume the newline character left by scanf
    
    do {
        printf("Masukkan jenis kendaraan (Motor, Mobil, Bus): ");
        scanf(" %s", type); getchar(); // consume the newline character left by scanf
    } while (strcmp(type, "Motor") != 0 && strcmp(type, "Mobil") != 0 && strcmp(type, "Bus") != 0);

    char parkID[6];
    strcpy(parkID, generateParkID(plate));
    int key = hashFunction(parkID);

    Vehicle* newVehicle = (Vehicle*)malloc(sizeof(Vehicle));
    strcpy(newVehicle->plate, plate);
    strcpy(newVehicle->type, type);
    strcpy(newVehicle->parkID, parkID);
    newVehicle->next = hashTable[key];
    hashTable[key] = newVehicle;

    printf("\nKendaraan berhasil ditambahkan!\n");
    printf("Nomor Plat: %s\n", plate);
    printf("Jenis: %s\n", type);
    printf("ID Parkir: %s\n\n", parkID);

    enterToContinue();
}

void listVehicles() {
    int empty = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Vehicle* current = hashTable[i];
        while (current) {
            printf("Nomor Plat: %s, Jenis: %s, ID Parkir: %s\n", current->plate, current->type, current->parkID);
            current = current->next;
            empty = 0;
        }
    }
    if (empty) printf("Tidak ada kendaraan yang terdaftar.\n");
    enterToContinue();
}

void removeVehicle() {
    listVehicles();
    char parkID[6];
    printf("Masukkan ID parkir kendaraan yang ingin dihapus: ");
    scanf(" %s", parkID); getchar();
    int key = hashFunction(parkID);

    Vehicle *current = hashTable[key], *prev = NULL;
    while (current) {
        if (strcmp(current->parkID, parkID) == 0) {
            if (prev) prev->next = current->next;
            else hashTable[key] = current->next;
            free(current);
            printf("Kendaraan dengan ID %s berhasil dihapus.\n", parkID);
            enterToContinue();
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("ID parkir tidak ditemukan.\n");
    enterToContinue();
}

int main() {
    srand(time(0));
    int choice;
    while (1) {
        system("clear");
        printf("\n=== Sistem Parkir MetroPark ===\n");
        printf("1. Tambah Kendaraan\n2. Lihat Daftar Kendaraan\n3. Hapus Kendaraan\n4. Keluar\nPilihan: ");
        scanf("%d", &choice); getchar();
        switch (choice) {
            case 1: addVehicle(); break;
            case 2: listVehicles(); break;
            case 3: removeVehicle(); break;
            case 4: puts("Thank You !"); return 0;
            default: printf("Pilihan tidak valid!\n");
        }
    }
}
