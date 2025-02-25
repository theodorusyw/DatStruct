#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 50

struct Data {
    char coin[5];
    double price;
    Data *next;
} *arr[SIZE];

int midSquare(char coin[]) {

}

void insert(char coin[], double price) {
    Data *data = (Data*)malloc(sizeof(Data));
    data->price = price;
    strcpy(data->coin, coin);
    data->next = NULL;

    int index = midSquare(coin);

}

int main() {
    insert("BTC", 97000.00);
    insert("ETH", 2700.00);
    insert("SOL", 172.59);
    insert("XRP", 2.57);

    return 0;
}