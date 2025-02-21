#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define HASH_SIZE 100
#define gc while(getchar()!='\n');

struct Booking {
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomtype[10];
    int stayduration;
    char bookingid[7];
    struct Booking* next;
}*bookings[HASH_SIZE];

int getHashKey(char* id) {
    int x = 0;
    for (int i = 2; i < 5; i++) {
        x += id[i]-'0';
    }
    return (x-1) % HASH_SIZE;
}

char toUpper(char x) {
    return 'a' <= x && x <= 'z' ? x - ('a'-'A'): x;
}

char* generateID(char* roomtype) {
    char *id = (char*)malloc(sizeof(char)*7);
    for (int i = 0; i < 5; i++) {
        id[i] = i < 2 ? toUpper(roomtype[i]) : rand()%10+'0';
    }
}

struct Booking* newBooking(char* fullname, char* phonenumber, int age, char* roomtype, int stayduration) {
    char* bookingid = generateID(roomtype);

    struct Booking* curr = (struct Booking*)malloc(sizeof(struct Booking));
    strcpy(curr->fullname, fullname);
    strcpy(curr->phonenumber, phonenumber);
    curr->age = age;
    strcpy(curr->roomtype, roomtype);
    curr->stayduration = stayduration;
    strcpy(curr->bookingid, bookingid);

    curr->next = NULL;

    return curr;
}

void pushTail(struct Booking* newData) {
    int hash = getHashKey(newData->bookingid);

    if (bookings[hash] == NULL) bookings[hash] = newData;
    else {
        struct Booking* curr = bookings[hash];
        while(curr->next) {
            curr = curr->next;
        }
        curr->next = newData;
    }
}

bool validFullName(char* fullname) {
    int len = strlen(fullname);
    return 3 <= len & len <= 30;
}

bool validPhoneNumber(char* phonenumber) {
    if (phonenumber[0] != '+' || phonenumber[1] != '6' || phonenumber[2] != '2') return false;

    int space = 0;
    int len = strlen(phonenumber);
    for (int i = 3; i < len; i++) {
        if (phonenumber[i] == ' ') space++;
    }
    return space >= 1 && len - (space + 3) == 11;
}

bool validAge(int age) {
    return age >= 18;
}

bool validRoomType(char* roomtype) {
    return strcmp(roomtype, "Deluxe") == 0 || strcmp(roomtype, "Reguler") == 0 || strcmp(roomtype, "Suite") == 0;
}

bool validStayDuration(int stayduration) {
    return 1 <= stayduration && stayduration <= 30;
}

void createBooking() {
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomtype[10];
    int stayduration;

    do {
        printf("Input Name: ");
        scanf("%[^\n]", fullname); gc
    } while(!validFullName(fullname));

    do {
        printf("Input Phone: ");
        scanf("%[^\n]", phonenumber); gc
    } while(!validPhoneNumber(phonenumber));
    
    do {
        printf("Input Age: ");
        scanf("%d", &age); gc
    } while(!validAge(age));
    
    do {
        printf("Input Room Type: ");
        scanf("%[^\n]", roomtype); gc
    } while(!validRoomType(roomtype));
    
    do {
        printf("Input Duration Stay: ");
        scanf("%d", &stayduration); gc
    } while(!validStayDuration(stayduration));

    pushTail(newBooking(fullname, phonenumber, age, roomtype, stayduration));
}

int main() {
    return 0;
}