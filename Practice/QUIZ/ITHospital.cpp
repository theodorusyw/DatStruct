#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
    int id;
    char name[20];
    int age;
    char status[10];
    int height;
    Node* left;
    Node* right;
} *node = NULL;

// mencari nilai lebih besar antara dua angka
int max(int a, int b) {
    return (a > b) ? a : b;
}

// mengembalikan tinggi node
int height(Node* root) {
    return (root == NULL) ? 0 : root->height;
}

// menghitung balance factor, jika > 1 atau < -1 maka tidak seimbang, perlu rotasi
int getBalance(Node* root) {
    return (root == NULL) ? 0 : height(root->left) - height(root->right);
}

// rotasi ke kanan
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return x;
}

// rotasi ke kiri
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = y;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// membuat node baru
Node* createNode(int id, char* name, int age, char* status) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->age = age;
    strcpy(newNode->status, status);
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
    int choice = -1;

    return 0;
}