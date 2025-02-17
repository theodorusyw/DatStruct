#include <stdio.h>
#include <stdlib.h>

typedef struct tnode {
    int value;
    struct tnode* left;
    struct tnode* right;
}tnode;

tnode* createNode(int value) {
    tnode* c = (tnode*)malloc(sizeof(tnode));
    c->value = value;
    c->left = NULL;
    c->right = NULL;
    return c;
}

tnode* buildBST(tnode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->value) {
        root->left = buildBST(root->left, value);
    } else {
        root->right = buildBST(root->right, value);
    }

    return root;
}

int search(tnode* root, int value) {
    if (root == NULL) {
        return -1;
    }

    if (root->value == value) {
        return root->value;
    } else if (value < root->value) {
        return search(root->left, value);
    } else if (value > root->value) {
        return search(root->right, value);
    }

    return root->value;
}

void inOrder(tnode* root) {
    if(root == NULL) return;

    inOrder(root->left);
    printf("%d", root->value);
    inOrder(root->right);
}

tnode* delNode(tnode* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->value) {
        root->left = delNode(root->left, value);
    } else if (value > root->value) {
        root->right = delNode(root->right, value);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->right == NULL) {
            tnode* temp = root->left;
            root->value = temp->value;
            root->left = NULL;
            free(temp);
        } else if (root->left == NULL) {
            tnode* temp = root->right;
            root->value = temp->value;
            root->right = NULL;
            free(temp);
        } else {
            tnode* temp = root->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }

            root->value = temp->value;
            root->left = delNode(root->left, temp->value);
        }
    }

    return root;
}

int main() {
    tnode* root = NULL;

    root = buildBST(root, 6);
    root = buildBST(root, 10);
    root = buildBST(root, 3);
    
    // printf("%d", root->value);

    int val = search(root, 10);
    // printf("%d", val);

    inOrder(root);
    printf("\n");
    delNode(root, 3);
    inOrder(root);

    return 0;
}