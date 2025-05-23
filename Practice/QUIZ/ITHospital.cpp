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
Node* rotateLeft(Node* x) {
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

Node* insertAVL(Node* root, int id, char* name, int age, char* status) {
    if(root == NULL) return createNode(id, name, age, status);

    if(id < root->id) {
        root->left = insertAVL(root->left, id, name, age, status);
    } else if(id > root->id) {
        root->right = insertAVL(root->right, id, name, age, status);
    } else {
        return root; // jika ID sudah ada
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if(balance > 1 && id < root->left->id) {
        return rotateRight(root);
    } 
    
    if(balance < -1 && id > root->left->id) {
        return rotateLeft(root);
    } 
    
    if(balance > 1 && id > root->left->id) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if(balance < -1 && id < root->left->id) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inOrder(Node* root) {
    if(root) {
        inOrder(root->left);
        printf("ID: %d, Name: %s, Age: %d, Status: %s\n", root->id, root->name, root->age, root->status);
        inOrder(root->right);
    }
}

void printUrgent(Node* root) {
    if(root) {
        printUrgent(root->left);

        if(strcmp(root->status, "Urgent") == 0) {
            printf("ID: %d, Name: %s, Age: %d, Status: %s\n", root->id, root->name, root->age, root->status);
        }

        printUrgent(root->right);
    }
}

void editPatient(Node* root, int id) {
    if(root == NULL) {
        printf("Patient with ID %d not foudn.\n", id);
        return;
    }

    if(id < root->id) {
        editPatient(root->left, id);
    } else if(id > root->id) {
        editPatient(root->right, id);
    } else {
        printf("Editing patient with ID: %d\n", root->id);
        printf("Current Name: %s\n", root->name);
        printf("Current Age: %d\n", root->age);
        printf("Current Status: %s\n", root->status);

        printf("Enter new name: ");
        scanf(" %[^\n]", root->name);
        printf("Enter new age: ");
        scanf("%d", &root->age);
        printf("Enter new status (Urgent/OK): ");
        scanf(" %[^\n]", root->status);

        printf("Patient data updated.\n");
    }
}

Node* deleteOkPatient(Node* root) {
    if(root == NULL) {
        return NULL;
    }

    root->left = deleteOkPatient(root->left);
    root->right = deleteOkPatient(root->right);

    if(strcmp(root->status, "OK") == 0) {
        printf("Deleting patient with ID: %d\n", root->id);
        root = deleteNode(root, root->id);
    }
}

int main() {
    int choice = -1;

    return 0;
}