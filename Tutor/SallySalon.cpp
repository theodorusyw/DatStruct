#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define gc getchar()

// Struct AVL Tree Node
struct Node {
    char name[105], cat[15], avail[15];
    int price;
    struct Node* left;
    struct Node* right;
    int height;
} *node = NULL;

// Function Declarations
int max(int a, int b);
int height(struct Node* root);
int bal(struct Node* root);
struct Node* leftRotate(struct Node* x);
struct Node* rightRotate(struct Node* x);
int validName(char* name);
void preOrder(struct Node* root);
void inOrder(struct Node* root);
void postOrder(struct Node* root);
int alreadyInTree(struct Node* root, char* name);
struct Node* createNode(char* name, int price, char* cat, char* avail);
struct Node* insertAVL(struct Node* root, struct Node* newNode);
struct Node* deleteAVL(struct Node* root, char* name);
void printMenu();
void enterToContinue();
struct Node* insert();
void view(struct Node* node);
struct Node* del(struct Node* root);

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* root) {
    return (root == NULL) ? 0 : root->height;
}

int bal(struct Node* root) {
    return (root == NULL) ? 0 : height(root->left) - height(root->right);
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    struct Node* z = y->right;

    y->right = x;
    x->left = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int validName(char* name) {
    if (strncmp(name, "Sally", 5) != 0 || strlen(name) < 5 || strlen(name) > 20) return -1;

    int space = 0, letterAfterSpace = 0, flag = 0, x = strlen(name);

    for (int i = 0; i < x; i++) {
        if(name[i] == ' ' && flag == 0) {
            space++;
            flag = 1;
        }
        if(name[i] != ' ' && flag == 1) {
            letterAfterSpace++;
            flag = 0;
        }
    }

    if(space > 0 && letterAfterSpace > 0) return 1;
    return -1;
}

void preOrder(struct Node* root) {
    if(root != NULL) {
        printf("Treatment    : %s\n", root->name);
        printf("Price        : %d\n", root->price);
        printf("Category     : %s\n", root->cat);
        printf("Availability : %s\n\n", root->avail);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node* root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("Treatment    : %s\n", root->name);
        printf("Price        : %d\n", root->price);
        printf("Category     : %s\n", root->cat);
        printf("Availability : %s\n\n", root->avail);
        inOrder(root->right);
    }
}

void postOrder(struct Node* root) {
    if(root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("Treatment    : %s\n", root->name);
        printf("Price        : %d\n", root->price);
        printf("Category     : %s\n", root->cat);
        printf("Availability : %s\n\n", root->avail);
    }
}

int alreadyInTree(struct Node* root, char* name) {
    if (root == NULL) return 0;
    if (strcmp(root->name, name) == 0) return 1;

    return alreadyInTree(root->left, name) || alreadyInTree(root->right, name);
}

struct Node* createNode(char* name, int price, char* cat, char* avail) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    strcpy(newNode->cat, cat);
    strcpy(newNode->avail, avail);
    newNode->price = price;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

struct Node* insertAVL(struct Node* root, struct Node* newNode) {
    if (root == NULL) return newNode;

    if (strcmp(newNode->name, root->name) < 0)
        root->left = insertAVL(root->left, newNode);
    else if (strcmp(newNode->name, root->name) > 0)
        root->right = insertAVL(root->right, newNode);
    else
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = bal(root);

    if (balance > 1) {
        if (strcmp(newNode->name, root->left->name) < 0)
            return rightRotate(root); // Left-Left
        else {
            root->left = leftRotate(root->left); // Left-Right
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (strcmp(newNode->name, root->right->name) > 0)
            return leftRotate(root); // Right-Right
        else {
            root->right = rightRotate(root->right); // Right-Left
            return leftRotate(root);
        }
    }
    return root;
}

struct Node* deleteAVL(struct Node* root, char* name) {
    if (root == NULL) return NULL;

    if (strcmp(name, root->name) < 0)
        root->left = deleteAVL(root->left, name);
    else if (strcmp(name, root->name) > 0)
        root->right = deleteAVL(root->right, name);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            struct Node* temp = root->left;
            while (temp->right)
                temp = temp->right;

            strcpy(root->name, temp->name);
            strcpy(root->cat, temp->cat);
            strcpy(root->avail, temp->avail);
            root->price = temp->price;

            root->left = deleteAVL(root->left, temp->name);
        }
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = bal(root);

    if (balance > 1) {
        if (bal(root->left) >= 0)
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (bal(root->right) <= 0)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void printMenu() {
    puts("1. View Available Treatment");
    puts("2. Insert Treatment");
    puts("3. Delete Treatment");
    puts("4. Exit");
}

void enterToContinue() {
    printf("ENTER to continue..."); gc;
}

struct Node* insert() {
    char name[101], cat[20], avail[50];
    int price;

    do {
        printf("Insert Name (start with Sally and include space): ");
        scanf(" %[^\n]", name); gc;
    } while(validName(name) == -1 || alreadyInTree(node, name) == 1);

    do {
        printf("Insert Price [50000 - 1000000]: ");
        scanf("%d", &price); gc;
    } while(price < 50000 || price > 1000000);

    do {
        printf("Insert Category [Hair Care | Nail Care | Body Care]: ");
        scanf(" %[^\n]", cat); gc;
    } while(strcmp(cat, "Hair Care") != 0 && strcmp(cat, "Nail Care") != 0 && strcmp(cat, "Body Care") != 0);

    do {
        printf("Insert Availability [Available | Unavailable]: ");
        scanf(" %[^\n]", avail); gc;
    } while(strcmp(avail, "Available") != 0 && strcmp(avail, "Unavailable") != 0);

    struct Node* newNode = createNode(name, price, cat, avail);
    node = insertAVL(node, newNode);

    printf("New treatment successfully inserted!\n");
    enterToContinue();
    return node;
}

void view(struct Node* node) {
    system("clear");

    if (node == NULL) {
        printf("No data.\n");
        enterToContinue();
        return;
    }

    char input[10];
    do {
        printf("Insert view mode [pre | in | post]: ");
        scanf("%s", input); gc;
    } while(strcmp(input, "pre") != 0 && strcmp(input, "in") != 0 && strcmp(input, "post") != 0);

    if(strcmp(input, "pre") == 0) preOrder(node);
    else if(strcmp(input, "in") == 0) inOrder(node);
    else postOrder(node);

    enterToContinue();
}

struct Node* del(struct Node* root) {
    system("clear");

    if (root == NULL) {
        printf("No data.\n");
        enterToContinue();
        return root;
    }
    
    char input[10];
    do {
        printf("Insert view mode [pre | in | post]: ");
        scanf("%s", input); gc;
    } while(strcmp(input, "pre") != 0 && strcmp(input, "in") != 0 && strcmp(input, "post") != 0);

    if(strcmp(input, "pre") == 0) preOrder(node);
    else if(strcmp(input, "in") == 0) inOrder(node);
    else postOrder(node);

    char name[101];
    printf("DELETE TREATMENT\n");
    printf("Insert name to be deleted: ");
    scanf(" %[^\n]", name); gc;

    if (alreadyInTree(root, name)) {
        root = deleteAVL(root, name);
        printf("Data successfully deleted!\n");
    } else {
        printf("Data not found.\n");
    }

    enterToContinue();
    return root;
}

int main() {
    int choice = -1;
    do {
        system("clear");
        printMenu();
        printf(">> ");
        scanf("%d", &choice); gc;
        switch(choice) {
            case 1: view(node); break;
            case 2: node = insert(); break;
            case 3: node = del(node); break;
            case 4: return 0;
        }
    } while(choice != 4);
    return 0;
}
