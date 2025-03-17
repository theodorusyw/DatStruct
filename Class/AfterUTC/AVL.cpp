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

node* createNode(int val){
	node* c = (node*) malloc(sizeof(node));
	c->val = val;
	c->height = 1;
	c->left = NULL;
	c->right = NULL;
	return c;
}

int height(node* root){
	if(root==NULL){
		return 0;
	}else{
		return root->height;
	}
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int getBalance(node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return height(root->left) - height(root->right);
    }
}

node* insert(node* root, int val){
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

    int balance
	
}


int main(){
	
	
	
	return 0;
}