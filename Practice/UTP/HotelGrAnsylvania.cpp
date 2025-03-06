#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define gc getchar();
#define clear system("clear");
#define TABLE_SIZE 100

typedef struct Node {
    char bookingID[6];
    char name[31];
    char phone[12];
    int age;
    char roomType[10];
    int duration;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

int calculateKey(char* bookingID) {
    int sum = bookingID[2] + bookingID[3] + bookingID[4] - 1;
    return sum % TABLE_SIZE;
}   

char* generateBookingID(char* roomType) {
    char* bookingID = (char*)malloc(6 * sizeof(char));
    snprintf(bookingID, 6, "%c%c%03d", toupper(roomType[0]), toupper(roomType[1]), rand() % 1000);
    return bookingID;
}

void enterToContinue() {
    puts("\nPress ENTER To Continue...");
    gc
}

int validName (char* name) {
    if (strlen(name) < 3 || strlen(name) > 30) {
        puts("Full name length must be between 3 and 30 characters!");
        return 0;
    }
    return 1;
}

int validPhone(char* phone) {
    if (strncmp(phone, "+62", 3) != 0 || phone[3] != ' ' || strlen(phone) != 15) {
        puts("Phone number must begin with '+62', contain a space, and the total length must be 11 (excluding '+62' and space)");
        return 0;
    }
    return 1;
}

int validAge(int age) {
    if (age < 18) {
        puts("Age must be minimum 18!");
        return 0;
    }
    return 1;
}

int validRoomType(char* roomType) {
    if (strcmp(roomType, "Standard") != 0 && strcmp(roomType, "Deluxe") != 0 && strcmp(roomType, "Suite") != 0) {
        puts("Room type must be either 'Standard', 'Deluxe', or 'Suite'!");
        return 0;
    }
    return 1;
}

int validDuration(int duration) {
    if (duration < 1 || duration > 30) {
        puts("You can't stay for less than 1 day or more than 30 days!");
        return 0;
    }
    return 1;
}

void printMenu() {
    clear
    puts("+-------------------+");
    puts("| Hotel GrAsylvania |");
    puts("+-------------------+");
    puts("");
    puts("1. Booking Hotel");
    puts("2. View Bookings");
    puts("3. Delete Booking");
    puts("4. Exit");
}

void bookingHotel() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        puts("Memory allocation failed");
        return;
    }

    do {
        printf("Enter your full name [3..30]: ");
        scanf("%[^\n]", newNode->name); gc
    } while (!validName(newNode->name));

    do {
        printf("Input phone number: ");
        scanf("%[^\n]", newNode->phone); gc
    } while(!validPhone(newNode->phone));   

    do {
        printf("Input Age [Minimum 18]: ");
        scanf("%d", &newNode->age); gc
    } while (!validAge(newNode->age));

    do {
        printf("Input Room Type [Standard, Deluxe, Suite]: ");
        scanf("%[^\n]", newNode->roomType); gc
    } while (!validRoomType(newNode->roomType));

    do {
        printf("Input how many night you will stay [1..30]: ");
        scanf("%d", &newNode->duration); gc
    } while (!validDuration(newNode->duration));

    strcpy(newNode->bookingID, generateBookingID(newNode->roomType));
    int key = calculateKey(newNode->bookingID);
    
    newNode->next = hashTable[key];
    hashTable[key] = newNode;

    printf("\n");
    printf("+================================+\n");
    printf("| Booking ID   : %-15s |\n", newNode->bookingID);
    printf("+================================+\n");
    printf("| Full Name    : %-15s |\n", newNode->name);
    printf("| Phone Number : %-15s |\n", newNode->phone);
    printf("| Room Type    : %-15s |\n", newNode->roomType);
    printf("| Night Stay   : %-6d night(s) |\n", newNode->duration);
    printf("+================================+\n");

    enterToContinue();
}

void viewBookings() {
    int isEmpty = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            isEmpty = 0;
            break;
        }
    }
    if (isEmpty) {
        puts("+=======================+");
        puts("| There is no booking ! |");
        puts("+=======================+");
        enterToContinue();
        return;
    }

    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            printf("+================================+\n");
            printf("| Booking ID   : %-15s |\n", current->bookingID);
            printf("+================================+\n");
            printf("| Full Name    : %-15s |\n", current->name);
            printf("| Phone Number : %-15s |\n", current->phone);
            printf("| Room Type    : %-15s |\n", current->roomType);
            printf("| Night Stay   : %-6d night(s) |\n", current->duration);
            printf("+================================+\n");
            current = current->next;
            found = 1;
        }
    }
    enterToContinue();
}

void deleteBooking() {
    int isEmpty = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            isEmpty = 0;
            break;
        }
    }
    if (isEmpty) {
        puts("+=======================+");
        puts("| There is no booking ! |");
        puts("+=======================+");
        enterToContinue();
        return;
    }


    char bookingID[6];
    viewBookings();

    printf("Enter Booking ID: ");
    scanf("%s", bookingID); gc

    int key = calculateKey(bookingID);
    Node *temp = hashTable[key], *prev = NULL;

    while (temp && strcmp(temp->bookingID, bookingID) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        puts("+--------------------------------------+");
        puts("| Failed to Delete, There is no data ! |");
        puts("+--------------------------------------+");
        enterToContinue();
        return;
    }

    if (prev) {
        prev->next = temp->next;
    }
    else {
        hashTable[key] = temp->next;
    }

    puts("+-------------------------------------------+");
    printf("| BookingID %s is Successfully Deleted ! |\n", temp->bookingID);
    puts("+-------------------------------------------+");

    enterToContinue();
}


int main() {
    int choice = 0;
    do {
        printMenu();
        do {
            printf(">> ");
            scanf("%d", &choice); gc
        } while (choice < 1 || choice > 4);

        switch (choice) {
            case 1: bookingHotel(); break;
            case 2: viewBookings(); break;
            case 3: deleteBooking(); break;
            case 4:
                puts("Thank you for using Hotel GrAsylvania!!!");
                enterToContinue();
                break;
        }
    } while (choice != 4);
}