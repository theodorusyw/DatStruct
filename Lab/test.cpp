#include <stdio.h>

#define HASH_SIZE 100

struct Booking {
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomtype[10];
    int stayduration;
    char bookingid[7];
    struct Booking* next;
}*bookings[HASH_SIZE];

int main() {

}