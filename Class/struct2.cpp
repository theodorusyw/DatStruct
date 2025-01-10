#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

struct Data {
    int id = 0;
    char title[100];
    int quantity;
};

Data* data = (Data*)malloc(sizeof(data));

int bookCount = 0;

void printMenu();
void enter();

void addBook();
void borrowBook();
void deleteStock();
void bookList();

int main() {
    do {
        int choice = -1;
        printMenu();

        do {
            printf(">> ");
            scanf("%d", &choice); gc
        } while (choice < 0 || choice > 5);

        switch (choice) {
            case 1 :
                puts("========================");
                addBook();
                break;
            case 2 :
                puts("========================");
                borrowBook();
                break;
            case 3 :
                puts("========================");
                deleteStock();
                break;
            case 4 :
                puts("========================");
                bookList();
                break;
            case 5 :
                puts("Thank You!!");
                enter();
                return 0;
        }
    } while (1);
    return 0;
}

void printMenu() {
    system("clear");
    puts("SUNIB University Library");
    puts("========================");
    puts("1. Add Book");
    puts("2. Borrow Book");
    puts("3. Delete Stock");
    puts("4. Book List");
    puts("5. Exit");
}

void enter() {
    printf("Press ENTER to continue..."); gc
}

void addBook() {
    // Book Name
    printf("Input Book Title : ");
    scanf("%[^\n]", data[bookCount].title); gc

    // Book Quantity
    printf("Input Book Quantity : ");
    scanf("%d", &data[bookCount].quantity); gc

    puts("Book has been successfully added");
    data[bookCount].id++;
    bookCount++;
    enter();
}

void bookList() {
    for (int i = 0; i < bookCount; i++) {
        printf("ID : %d\n", data[i].id);
        printf("Title : %s\n", data[i].title);
        printf("Quantity : %d\n", data[i].quantity);
        puts("=====================");
    }
    enter();
}

void borrowBook() {
    if (bookCount == 0) {
        puts("There is no book");
        enter();
        return;
    }
    bookList();
    char validation[100];
    do {
        printf("Choose between id or title [id / title] : ");
        scanf("%s", validation); gc
    } while (strcmp(validation, "id") != 0 && strcmp(validation, "title") != 0);

    int idx = -1;
    if (strcmp(validation, "title") == 0) {
        do {
            char temp[100];
            printf("Input Book Title : ");
            scanf("%[^\n]", temp); gc

            for (int i = 0; i < bookCount; i++) {
                if (strcmp(temp, data[i].title) == 0) {
                    idx = i;
                    break;
                }
            }
        } while (idx == -1);
    } else {
        do {
            printf("Input Book ID : ");
            scanf("%d", &idx); gc
            idx --;
        } while (idx < 0 || idx > bookCount);
    }
    
    puts("Book has been successfully Booked");
    data[idx].quantity--;
    enter();
}

void deleteStock() {
    if (bookCount == 0) {
        puts("There is no book");
        enter();
        return;
    }
    bookList();
    int temp;
    do {
        printf("Input Book ID : ");
        scanf("%d", &temp); gc
        temp--;
    } while (temp < 0 || temp > bookCount);

    for (int i =- 0; i < bookCount - 1; i++) {
        data[i] = data[i + 1];
    }
    bookCount--;
    puts("Book has been succesfully deleteStocketed");
    enter();
}