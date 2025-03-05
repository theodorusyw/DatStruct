#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();
#define clear system("clear");

struct Node {
    char nama[100];
    char tipe[100];
    int jumlah;
    double jarak;
    char alamat[100];
    int priority;
    char priorityStr[100];
    Node* next;
} *head, *tail;

void priceList() {
    puts("----------------------------------");
    puts("| Menu            | Price        |");
    puts("----------------------------------");
    puts("| Pizza           | $8           |");
    puts("| Burgers         | $6           |");
    puts("| Sushi           | $12          |");
    puts("| Tacos           | $7           |");
    puts("| Pasta           | $10          |");
    puts("----------------------------------");
}

void printMenu() {
    clear
    puts("## Delicoius Delights Food Order Management System ##");
    priceList();
    puts("1. Add Order");
    puts("2. Process Order");
    puts("3. Display Queue");
    puts("4. Exit");
}

void enterToContinue() {
    puts("Press ENTER To Continue..."); gc
}

Node* createNode(char* nama, char* tipe, int jumlah, double jarak, char* alamat, int priority) {
    Node* current = (Node*)malloc(sizeof(Node));

    strcpy(current->nama, nama);
    strcpy(current->tipe, tipe);
    current->jumlah = jumlah;
    current->jarak = jarak;
    strcpy(current->alamat, alamat);
    current->priority = priority;

    if (priority == 0) {
        strcpy(current->priorityStr, "Standard");
    } else if (priority == 1) {
        strcpy(current->priorityStr, "Rush");
    } else if (priority == 2) {
        strcpy(current->priorityStr, "High Priority");
    }

    current->next = NULL;

    return current;
}

void push(Node* current) {
    if (head == NULL) {
        head = tail = current;
    } else if (current->priority > head->priority) {
        current->next = head;
        head = current;
    } else if (current->priority <= tail->priority) {
        tail->next = current;
        tail = current;
    } else {
        Node* temp = head;
        while (temp != NULL & temp->next->priority >= current->priority) {
            temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
    }
}

bool pop(char* nama) {
    if (strcmp(head->nama, nama) == 0) {
        Node* temp = head;
        head = temp->next;
        free(temp);
        return true;
    } else {
        Node* temp = head;
        while (temp != NULL && strcmp(temp->next->nama, nama) != 0) {
            temp = temp->next;
        }
        Node* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        return true;
    }
    return false;
}

bool validNama(char* nama) {
    return strlen(nama) <= 20;
}

bool validTipe(char* tipe) {
    return strcmp(tipe, "Pizza") == 0 || strcmp(tipe, "Burgers") == 0 || strcmp(tipe, "Sushi") == 0 || strcmp(tipe, "Tacos") == 0 || strcmp(tipe, "Pasta") == 0;
}

bool validJumlah(int jumlah) {
    return jumlah >= 1;
}

bool validJarak(int jarak) {
    return jarak <= 10 && jarak >= 1;
}

bool validAlamat(char* alamat) {
    return strlen(alamat) <= 30;
}

bool validPriority(int priority) {
    return priority <= 2 && priority >= 0;
}

void addOrder() {
    clear
    priceList();

    char nama[100];
    char tipe[100];
    int jumlah;
    double jarak;
    char alamat[100];
    int priority;
    char priorityStr[100];
    Node* next;

    // nama
    do {
        printf("Enter Customer Name (max 20 character): ");
        scanf("%[^\n]", nama); gc
        if (!validNama(nama)) puts("Enter less than 20 Character!!");
    } while(!validNama(nama));

    // tipe
    do {
        printf("Select Food (Pizza, Burgers, Sushi, Tacos, Pasta): ");
        scanf("%[^\n]", tipe); gc
        if (!validTipe(tipe)) puts("Wrong Type, Please enter from the list!!");
    } while(!validTipe(tipe));
    
    // jumlah
    do {
        printf("Enter Quantity (must be at least 1): ");
        scanf("%d", &jumlah); gc
        if (!validJumlah(jumlah)) puts("Enter more than 1!!");
    } while(!validJumlah(jumlah));
    
    // jarak
    do {
        printf("Enter Distance (min. 1 km, max. 10 km): ");
        scanf("%lf", &jarak); gc
        if (!validJarak(jarak)) puts("Enter more than 1 km and less than 10 km");
    } while(!validJarak(jarak));
    
    // alamat
    do {
        printf("Enter Delivery Address (max 30 character): ");
        scanf("%[^\n]", alamat); gc
        if (!validAlamat(alamat)) puts("Enter less than 30 Character!!");
    } while(!validAlamat(alamat));
    
    // priority
    do {
        printf("Enter Priority (0 for standard, 1 for rush, 2 for high priority): ");
        scanf("%d", &priority); gc
        if (!validPriority(priority)) puts("Enter between 0, 1, 2!!");
    } while(!validPriority(priority));

    push(createNode(nama, tipe, jumlah, jarak, alamat, priority));
    puts("Order added");
    enterToContinue();
}

void processOrder() {

}

void displayQueue() {

}

int main() {
    do {
        int inp = -1;
        printMenu();
        do {
            printf("Enter your choice: ");
            scanf("%d", &inp); gc
        } while (inp < 1 || inp > 4);

        switch (inp) {
            case 1:
                addOrder();
                break;
            case 2:
                processOrder();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                clear
                printf("Thank you\nExiting the program...\n");
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}

