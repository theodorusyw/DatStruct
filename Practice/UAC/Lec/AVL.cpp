// insert, delete, max, height, getBalance, rotateLeft, rotateRight, preOrder, inOrder, postOrder, alreadyInTree

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[101];
    int price;
    int height;
    struct Node* left;
    struct Node* right;
}*node = NULL;

int count = 0;

Node* createNode(char* name, int price, int height) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->price = price;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Node* root) {
    if (root == NULL) return 0;
    return root->height;
}

int getBalance(Node* root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* z = y->left;

    y->right = x;
    x->left = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* rotateRight(Node* x) {
    Node* y = x->left;
    Node* z = y->right;

    y->left = x;
    x->right = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* root, Node* newNode) {
    if (root == NULL) {
        return newNode;
    } else if (strcmp(root->name, newNode->name) > 0) {
        root->left = insert(root->left, newNode);
    } else if (strcmp(root->name, newNode->name) < 0) {
        root->right = insert(root->right, newNode);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    if (balance < - 1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

Node* deleteAVL(Node* root, char* name) {
    if (root == NULL) {
        return NULL;
    } else if (strcmp(root->name, name) > 0) {
        root->left = deleteAVL(root->left, name);
    } else if (strcmp(root->name, name) < 0) {
        root->right = deleteAVL(root->right, name);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    if (balance < - 1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}