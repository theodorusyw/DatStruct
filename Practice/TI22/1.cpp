#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 50

struct Data {
    char coin[5];
    double price;
    Data *next;
} *arr[SIZE];

int midSquare(const char coin[]) {
    int key = 0;
    for(int i = 0; coin[i] != '\0'; i++) key += coin[i];
    int square = key * key;
    char temp[20];
    snprintf(temp, sizeof(temp), "%d", square);

    int temp_len = strlen(temp);
    int digits = (temp_len % 2 == 0) ? 2 : 3;
    int startPos = (temp_len - digits)/2;
    char mid[4] = {0};
    strncpy(mid, temp + startPos, digits);
    // mid[4] = '\0';
    int res = atoi(mid);
    return res % SIZE;
}

void insert(const char coin[], double price) {
    Data *data = (Data*)malloc(sizeof(Data));
    data->price = price;
    strcpy(data->coin, coin);
    data->next = NULL;

    int index = midSquare(coin);
    if (!arr[index]) arr[index] = data;
    else {
        Data *temp = arr[index];
        while(temp->next) temp = temp->next;
        temp->next = data;
    }
    printf("%s at index %d\n", coin, index);
}

int main() {
    insert("BTC", 97000.00);
    insert("ETH", 2700.00);
    insert("SOL", 172.59);
    insert("XRP", 2.57);

    return 0;
}