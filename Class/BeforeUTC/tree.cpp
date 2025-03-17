#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct tnode {
    char value;
    tnode* left;
    tnode* right;
} tnode;

tnode* createNode (char value) {
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int isOperator(char c) {
    return(c == '+' || c == '-' || c == '/' || c == '*' || c == '^');
}

void buildPreTree(tnode** root, char* prefeq, int* pos) {
    if (*root == NULL) {
        *root = createNode(prefeq[*pos]);
    }
    if (isOperator(prefeq[*pos])) {
        *pos = *pos + 1;
        (*root)->left = createNode(prefeq[*pos]);
        buildPreTree((&(*root)->left), prefeq, pos);

        *pos = *pos + 1;
        (*root)->right = createNode(prefeq[*pos]);
        buildPreTree((&(*root)->right), prefeq, pos);
    }
}

tnode* buildPostTree(char* postfix) {
    tnode* stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        tnode* newNode = createNode(postfix[i]);

        if (isdigit(postfix[i])) {
            stack[++top] = newNode;
        } else if (isOperator(postfix[i])) {
            newNode->left = stack[--top];
            newNode->right = stack[--top];
            stack[++top] = newNode;
        }
    }

    return stack[top];
}

int evaluate(tnode* root) {
    if (root->value == '+') {
        return evaluate(root->left) + evaluate(root->right);
    } else if (root->value == '-') {
        return evaluate(root->left) - evaluate(root->right);
    } else if (root->value == '*') {
        return evaluate(root->left) * evaluate(root->right);
    } else if (root->value == '/') {
        return evaluate(root->left) / evaluate(root->right);
    } else if (root->value == '^') {
        return (int) pow(evaluate(root->left), evaluate(root->right));
    } else {
        return root->value - '0';
    }
}

void inOrder(tnode* root) {
    if (root != NULL) {
        if (isOperator(root->value)) printf("(");
        inOrder(root->left);
        printf("%c", root->value);
        inOrder(root->right);
        if (isOperator(root->value)) printf(")");
    }
}

void preOrder(tnode* root) {
    if (root != NULL) {
        printf("%c", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(tnode* root) {
    if (root != NULL) {
        printf("%c", root->value);
        postOrder(root->left);
        postOrder(root->right);
    }
}

int main() {
    char prefeq[] = "+*234";
    char posfeq[] = "351+^";
    int pos = 0;
    tnode* root = NULL;

    buildPreTree(&root, prefeq, &pos);

    inOrder(root);
    printf("\n");
    
    int res = evaluate(root);
    printf("Hasil Akhir : %d\n", res);
    
    // preOrder(root);
    // printf("\n");

    // postOrder(root);
    // printf("\n");

    return 0;
}