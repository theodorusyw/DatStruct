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

node* insertNode(node* root, int val) {
	if(root == NULL){
		return createNode(val);
	}else if(val < root->val){
		root->left = insertNode(root->left, val);
	}else if(val > root->val){
		root->right = insertNode(root->right, val);
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

    return root;
}

node* minValueNode(node* root) {
    node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

node* deleteNode(node* root, int val) {
    if (root == NULL) {
        return root;
    }

    if (val < root->val) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->val) {
        root->right = deleteNode(root->right, val);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            node* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return RightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return RightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = RightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void display(node* root) {
    if (root != NULL) {
        display(root->left);
        printf("%d ", root->val);
        display(root->right);
    }
}

int main() {
	node* root = NULL;

    root = insertNode(root, 20);
    root = insertNode(root, 15);
    root = insertNode(root, 25);
    root = insertNode(root, 10);
    root = insertNode(root, 30);
    root = insertNode(root, 5);

    display(root);
    printf("\n");

    root = deleteNode(root, 10);

    display(root);
    printf("\n");

    printf("Root: %d\n", root->val);

	return 0;
}