#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nama[50];
    int labaBersih;
    int hpp;
    int labaKotor;
} UMKM;

UMKM heap[MAX];
int heapSize = 0;

void swap(UMKM* a, UMKM* b) {
    UMKM temp = *a;
    *a = *b;
    *b = temp;
}

void upHeap(int i) {
    int parent = (i - 1) / 2;
    if (i && heap[i].labaBersih > heap[parent].labaBersih) {
        swap(&heap[i], &heap[parent]);
        upHeap(parent);
    }
}

void downHeap(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < heapSize && heap[left].labaBersih > heap[largest].labaBersih) {
        largest = left;
    }
    if (right < heapSize && heap[right].labaBersih > heap[largest].labaBersih) {
        largest = right;
    }
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        downHeap(largest);
    }
}

void insert(char nama[], int labaKotor, int hpp) {
    UMKM u;
    strcpy(u.nama, nama);
    u.hpp = hpp;
    u.labaKotor = labaKotor;
    u.labaBersih = labaKotor + hpp; // dari rumus: labaKotor = labaBersih - HPP
    heap[heapSize] = u;
    upHeap(heapSize++);
}

UMKM extract() {
    UMKM max = heap[0];
    heap[0] = heap[--heapSize];
    downHeap(0);
    return max;
}

int main() {
    insert("Cilokal", 1000, 250);
    insert("Eserut", 500, 100);
    insert("SotoMadura", 700, 300);
    insert("BebekBarokah", 750, 50);
    insert("PijaHat", 1800, 1100);
    insert("Kaepce", 800, 30);
    insert("SoBakso", 300, 50);
    insert("AyamMoza", 2000, 200);
    insert("CirengHot", 1200, 400);

    printf("Prioritas Pendanaan UMKM berdasarkan Laba Bersih (terbesar ke terkecil): ");
    while (heapSize > 0) {
        UMKM top = extract();
        printf("%s, ", top.nama);
    }
    
    return 0;
}