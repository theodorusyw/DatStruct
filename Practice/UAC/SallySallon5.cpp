#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

struct Node {
    char name[101];
    int price;
    char cate[101];
    char avail[101];
    int height;
    struct Node* left;
    struct Node* right;
} *node = NULL;

int count = 0;

Node* createNode(char* name, int price, char* cate, char* avail) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->price = price;
    strcpy(newNode->cate, cate);
    strcpy(newNode->avail, avail);
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void enterToContinue() {
    puts("Press ENTER to Continue...");
    gc
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

int validName(char* name) {
    if(strncmp(name, "Sally", 5) != 0 || strlen(name) < 10 || strlen(name) > 25){
		return -1; 
	}
	
	int space = 0, letterAfterSpace = 0, flag = 0, x = strlen(name); 
	
	for(int i=0; i<x; i++){
		if(name[i] == ' ' && flag == 0){
			space++; 
			flag = 1; 
		}
		if(name[i] != ' ' && flag == 1){
			letterAfterSpace++; 
			flag = 0; 
		}
	}
	
	if(space > 0 && letterAfterSpace > 0) return 1; 
	return -1;
}

Node* insertAVL(Node* root, Node* newNode) {
    if (root == NULL) {
        return newNode;
    } else if (strcmp(root->name, newNode->name) > 0) {
        root->left = insertAVL(root->left, newNode);
    } else if (strcmp(root->name, newNode->name) < 0) {
        root->right = insertAVL(root->right, newNode);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root);
            return rotateRight(root);
        }
    }

    if (balance < 1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root);
            return rotateLeft(root);
        }
    }

    return root;
}

Node* deleteAVL(Node* root, char* name) {
    
}

int main() {
    int choice = -1;

    do {
        do {
            puts("Sally Sallon");
            puts("1. Insert Menu");
            puts("2. View Menu");
            puts("3. Delete Menu");
            puts("4. Exit");
            printf(">> ");
            scanf("%d", &choice); gc
        } while(choice < 1 || choice > 4);

        switch (choice)
        {
        case 1:
            node = insertMenu(node);
            break;
        case 2:
            viewMenu(node);
            break;
        case 3:
            node = deleteMenu(node);
            break;
        case 4:
            puts("Exiting...");
            return 0;
        default:
            puts("Invalid input");
            break;
        }
    } while(1);

    return 0;
}