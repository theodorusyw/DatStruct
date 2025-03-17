#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct node{
	int val;
	int height;
	struct node* left;
	struct node* right;
};

node* createNode(int val) {
	node* c = (node*) malloc(sizeof(node));
	c->val = val;
	c->height = 1;
	c->left = NULL;
	c->right = NULL;
	return c;
}

int height(node* root) {
	if(root==NULL){
		return 0;
	}else{
		return root->height;
	}
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int getBalance(node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return height(root->left) - height(root->right);
    }
}

node*  leftRotate(node* x) {
    node* y = x->right;
    node* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

node* RightRotate(node* y) {
    node* x = y->left;
    node* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

node* insert(node* root, int val) {
	if(root == NULL){
		return createNode(val);
	}else if(val < root->val){
		root->left = insert(root->left, val);
	}else if(val > root->val){
		root->right = insert(root->right, val);
	}else{
		return root;
	}
	
	root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && val < root->left->val) {
        return RightRotate(root);
    }

    if (balance < -1 && val > root->right->val) {
        return leftRotate(root);
    }

    if (balance > 1 && val > root->left->val) {
        root->left = leftRotate(root->left);
        return RightRotate(root);
    }

    if (balance < -1 && val < root->right->val) {
        root->right = RightRotate(root->right);
        return leftRotate(root);
    }
}


int main() {
	node* root = NULL;

    root = insert(root, 20);
    root = insert(root, 15);
    root = insert(root, 25);
    
	return 0;
}