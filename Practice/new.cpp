#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Visitor {
    char name[50];
    char tiket[10];
    struct Visitor *next;
    struct Visitor *prev;
} Visitor;

int main() {
    return 0;
}