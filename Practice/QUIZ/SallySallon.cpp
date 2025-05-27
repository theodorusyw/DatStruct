#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    char name[101];
    int price;
    char cate[20];
    char avail[20];
    int height;
    struct Node* left;
    struct Node* right;
}*node = NULL;

int count = 0;

Node* createNode(char* name, int price, char* cate, char* avail) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->cate, cate);
    strcpy(newNode->avail, avail);
    newNode->price = price;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void enterToContinue() {
    printf("Press enter to continue...\n");
    getchar();
}

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Node* root) {
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* rotateRight(Node* x) {
    Node* y = x->left;
    Node* z = y->right;

    y->right = x;
    x->left = z;

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
    if(root == NULL) return newNode;
    else if(strcmp(root->name, newNode->name) > 0) root->left = insertAVL(root->left, newNode);
    else if(strcmp(root->name, newNode->name) < 0) root->right = insertAVL(root->right, newNode);
    else return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    
    int balance = getBalanceFactor(root);

    if (balance > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rotateRight(root);
        } else { 
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    if (balance < -1) {
        if (getBalanceFactor(root->right) >= 0) {
            return rotateLeft(root);
        } else { 
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}

int main() {
    return 0;
}