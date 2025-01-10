#include <stdio.h>
#include <stdlib.h>

struct Student {
    int age;
    int height;
};

int main () {
    struct Student student;

    // akses anggota struct5
    student.age = 20;
    student.height = 170;

    // Alokasi memori untuk struct
    struct Student* ptr2  = (Student*)malloc(sizeof(struct Student));
}