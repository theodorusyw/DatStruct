#include <stdio.h>
#include <string.h>

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

    printf("Input Name: ");
    scanf("%[^\n]", fullname); gc

    printf("Input Phone: ");
    scanf("%[^\n]", phonenumber); gc
    
    printf("Input Age: ");
    scanf("%d", &age); gc
    
    printf("Input Room Type: ");
    scanf("%[^\n]", roomtype); gc
    
    printf("Input Duration Stay: ");
    scanf("%d", &stayduration); gc
}

int main() {
    return 0;
}