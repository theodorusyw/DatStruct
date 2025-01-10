#include <stdio.h>
#include <stdlib.h>

struct Student {
    int age;
    int height;
}arrStudent[5];

int main () {
    Student student;

    // akses anggota struct5
    student.age = 20;
    student.height = 170;

    // Alokasi memori untuk struct
    struct Student* ptr2  = (Student*)malloc(sizeof(struct Student));

    // Akses anggota dari struct pointer
    ptr2->age = 12;
    ptr2->height = 175;

    printf("Age: %d, height: %d", ptr2->age, ptr2->height);

    // melepaskan alokasi memori
    free(ptr2);

    // akses anggota dari array of struct
    arrStudent[0].age = 12;
    arrStudent[1].age = 13;
}