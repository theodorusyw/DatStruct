#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Mahasiswa {
    int age;
    char name[100];
    struct Mahasiswa* right;
    struct Mahasiswa* left;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Mahasiswa* curr) {
    return (curr == NULL) ? 0 : curr->height;
}

int getBalance(struct Mahasiswa* curr) {
    return (curr == NULL) ? 0 : getHeight(curr->left) - getHeight(curr->right);
}

struct Mahasiswa* createNewMhs(int age, char name[100]) {
    struct Mahasiswa* newMhs = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
    newMhs->age = age;
    strcpy(newMhs->name, name);
    newMhs->left = NULL;
    newMhs->right = NULL;
    newMhs->height = 1;
    return newMhs;
}

struct Mahasiswa* rightRotate(struct Mahasiswa* curr) {
    struct Mahasiswa* currLeft = curr->left;
    struct Mahasiswa* currLeftRight = currLeft->right;

    currLeft->right = curr;
    curr->left = currLeftRight;

    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
    currLeft->height = max(getHeight(currLeft->left), getHeight(currLeft->right)) + 1;

    return currLeft;
}

struct Mahasiswa* leftRotate(struct Mahasiswa* curr) {
    struct Mahasiswa* currRight = curr->right;
    struct Mahasiswa* currRightLeft = currRight->left;

    currRight->left = curr;
    curr->right = currRightLeft;

    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
    currRight->height = max(getHeight(currRight->left), getHeight(currRight->right)) + 1;

    return currRight;
}

struct Mahasiswa* insertAVL(struct Mahasiswa* curr, int age, char name[100]) {
    if (curr == NULL) {
        return createNewMhs(age, name);
    }
    
    if (age < curr->age)
        curr->left = insertAVL(curr->left, age, name);
    else if (age > curr->age)
        curr->right = insertAVL(curr->right, age, name);
    else
        return curr;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    int balance = getBalance(curr);

    if (balance > 1 && age < curr->left->age)
        return rightRotate(curr);
    if (balance < -1 && age > curr->right->age)
        return leftRotate(curr);
    if (balance > 1 && age > curr->left->age) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if (balance < -1 && age < curr->right->age) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

void inOrder(struct Mahasiswa *curr) {
    if (curr != NULL) {
        inOrder(curr->left);
        printf("Age: %d, Name: %s\n", curr->age, curr->name);
        inOrder(curr->right);
    }
}

void updateTree(Mahasiswa* root, int age, char newName[100]){
	if(!root) printf("Not Found\n");
	
	else if(age < root->age){
		updateTree(root->left, age, newName);
	}
	
	else if(age > root->age){
		updateTree(root->right, age, newName);
	}
	
	else if(age == root->age){
		strcpy(root->name, newName);
		printf("Name Updated\n");
	}
	
}

int main() {
    struct Mahasiswa* root = NULL;
    root = insertAVL(root, 3, "Cindy");
    root = insertAVL(root, 18, "Alex");
    root = insertAVL(root, 21, "Brian");
    root = insertAVL(root, 8, "David");
    root = insertAVL(root, 7, "Ella");
    root = insertAVL(root, 6, "Fiona");
    root = insertAVL(root, 23, "George");
    
    printf("In-order traversal:\n");
    inOrder(root);
    
    updateTree(root, 21, "Jov");
    root = insertAVL(root, 18, "Alex");
    root = insertAVL(root, 21, "Brian");
    root = insertAVL(root, 8, "David");
    root = insertAVL(root, 7, "Ella");
    root = insertAVL(root, 6, "Fiona");
    root = insertAVL(root, 23, "George");
    
    printf("In-order traversal:\n");
    inOrder(root);
    
    updateTree(root, 21, "Jovita");
    printf("===================\nAfter update:\n");
    inOrder(root);
    return 0;
}