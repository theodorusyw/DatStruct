#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id;
    int value;
    int interAchiev;
    int height;
    struct Node *left, *right;
};

int getValue(int exam_pass, int have_c_grade) {
    if (exam_pass == 0 && have_c_grade == 1) return 0;
    if (exam_pass == 0 && have_c_grade == 0) return 1;
    if (exam_pass == 1 && have_c_grade == 1) return 2;
    return 3;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int height(struct Node* root) {
    return root ? root->height : 0;
}

int getBalance(struct Node* root) { 
    return root ? height(root->left) - height(root->right) : 0;
}

struct Node* createNode(int id, int value, int achiev) {
    struct Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->value = value;
    newNode->interAchiev = achiev;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->left;
    struct Node* T2 = y->right;
    
    y->right = x;
    x->left = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int compare(struct Node* a, struct Node* b) {
    if(a->value != b->value) return a->value - b->value;
    if(a->interAchiev != b->interAchiev) return a->interAchiev - b->interAchiev;
    return a->id - b->id;
}

struct Node* insert(struct Node* root, struct Node* newNode) {
    if(!root) return newNode;

    if(compare(newNode, root) < 0) {
        root->left = insert(root->left, newNode);
    } else if(compare(newNode, root) > 0) {
        root->right = insert(root->right, newNode);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if(balance > 1) {
        if (compare(newNode, root->left) < 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    if(balance < -1) {
        if(compare(newNode, root->right) > 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

struct Node* findMax(struct Node* root) {
    while(root->right) {
        root = root->right;
    }
    return root;
}

struct Node* deleteNode(struct Node* root, int id) {
    if(!root) return NULL;

    if(id < root->id) {
        root->left = deleteNode(root->left, id);
    } else if(id > root->id) {
        root->right = deleteNode(root->right, id);
    } else {
        if(!root->left || !root->right) {
            struct Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }

        struct Node* temp = findMax(root->left);
        root->id = temp->id;
        root->value = temp->value;
        root->interAchiev = temp->interAchiev;
        root->left = deleteNode(root->left, temp->id);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if(balance > 1) {
        if(getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    if(balance < -1) {
        if(getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    
    return root;
}

void collectTop(struct Node* root, int* ids, int* idx) {
    if(!root || *idx >= 3) return;
    collectTop(root->right, ids, idx);
    if( *idx < 3) {
        ids[(*idx)++] = root->id;
    }
    collectTop(root->left, ids, idx);
}

int main() {
    int n;
    scanf("%d", &n);
    struct Node* root = NULL;

    for(int i = 0; i < n; i++) {
        char type;
        scanf(" %c", &type);


        if(type == 'i') {
            int id;
            int exam_pass;
            int c_grade;
            int ach;
            scanf("%d %d %d %d", &id, &exam_pass, &c_grade, &ach);
            int value = getValue(exam_pass, c_grade);
            struct Node* newNode = createNode(id, value, ach);
            root = insert(root, newNode);
        } else if(type == 'd') {
            int id;
            scanf("%d", &id);
            root = deleteNode(root, id);
        }
    }

    int top[3] = {0};
    int idx = 0;
    collectTop(root, top, &idx);
    for(int i = 0; i < idx; i++) {
        printf("%d", top[i]);
        if(i < idx - 1) printf(" ");
    }
    puts("");

    return 0;
}