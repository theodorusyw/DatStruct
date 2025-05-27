#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define gc getchar();

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
    return root->height;
}

int getBalanceFactor(Node* root) {
    if (root == NULL) return 0;
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
        if (getBalanceFactor(root->right) <= 0) {
            return rotateLeft(root);
        } else { 
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}

Node* deleteAVL(Node* root, char* name) {
    if (root == NULL) {
        return NULL;
    } else if (strcmp(root->name, name) > 0) {
        root->left = deleteAVL(root->left, name);
    } else if (strcmp(root->name, name) < 0) {
        root->right = deleteAVL(root->right, name);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
        } else {
            Node* temp = root->left;

            while (temp->right) {
                temp = temp->right;
            }

            strcpy(root->name, temp->name);
            strcpy(root->cate, temp->cate);
            strcpy(root->avail, temp->avail);
            root->price = temp->price;

            root->left = deleteAVL(root->left, temp->name);
        }
    }

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
        if (getBalanceFactor(root->right) <= 0) {
            return rotateLeft(root);
        } else { 
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}

Node* insertMenu(Node* root) {
    char name[101];
    char cate[101];
    char avail[101];
    int price;

    do {
        printf("Insert Name: ");
        scanf("%[^\n]", name); gc
    } while (validName(name) == -1);

    do {
        printf("Insert Price [50.000 - 1.000.000]: ");
        scanf("%d", &price); gc
    } while (price < 50000 || price > 1000000);

    do {
        printf("Insert Category [Hair Care | Nail Care | Body Care]: ");
        scanf("%[^\n]", cate); gc
    } while (strcmp(cate, "Hair Care") != 0 && strcmp(cate, "Nail Care") != 0 && strcmp(cate, "Body Care") != 0);

    do {
        printf("Insert Availibility [available | Not Available]: ");
        scanf("%s", avail); gc
    } while (strcmp(avail, "Available") != 0 && strcmp(avail, "Unavailable") != 0);

    Node* newNode = createNode(name, price, cate, avail);
    root = insertAVL(root, newNode);

    printf("Data successfully inserted!\n");
    enterToContinue();

    return root;
}

void viewMenu(Node *root) {
    if (root == NULL) {
        printf("No data available.\n");
        enterToContinue();
        return;
    }
    
    char input[10];
    
    
    do {
        printf("Insert View Mode [pre | in | post]: ");
        scanf("%s", input); gc
    } while (strcmp(input, "pre") != 0 && strcmp(input, "in") != 0 && strcmp(input, "post") != 0);
    
    if (strcmp(input, "pre") == 0) {
        preOrder(root);
    } else if (strcmp(input, "in") == 0) {
        inOrder(root);
    } else {
        postOrder(root);
    }
    
    enterToContinue();
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf("Treatment   : %s\n", root->name);
        printf("Price       : %d\n", root->price);
        printf("Category    : %s\n", root->cate);
        printf("Availablity : %s\n", root->avail);
        
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);

        printf("Treatment   : %s\n", root->name);
        printf("Price       : %d\n", root->price);
        printf("Category    : %s\n", root->cate);
        printf("Availablity : %s\n", root->avail);
        
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        
        printf("Treatment   : %s\n", root->name);
        printf("Price       : %d\n", root->price);
        printf("Category    : %s\n", root->cate);
        printf("Availablity : %s\n", root->avail);
    }
}

int alreadyInTree(Node* root, char* name) {
    if (root == NULL) return -1;
    if (strcmp(root->name, name) == 0) return 1;

    int leftSide = alreadyInTree(root->left, name);
    if (leftSide == 1) return 1;
    return alreadyInTree(root->right, name);
}

Node* deleteMenu(Node* root) {
    if (root == NULL) {
        printf("No data available.\n");
        enterToContinue();
        return root;
    }

    char name[101];

    printf("Insert Name to Delete: ");
    scanf("%[^\n]", name); gc

    if (alreadyInTree(root, name) == -1) {
        root = deleteAVL(root, name);
        printf("Data successfully deleted!\n");
        count--;
    } else {
        printf("Data Not Found!\n");
    }
    enterToContinue();

    return root;
}

int main() {
    int choice = -1;

    do {
        do {
            system("clear");
            printf("===================\n");
            printf("SALLY SALON\n");
            printf("===================\n");
            printf("1. Insert Treatment\n");
            printf("2. View Treatments\n");
            printf("3. Delete Treatment\n");
            printf("4. Exit\n");
            printf("===================\n");
            printf("Choose an option: ");
            scanf("%d", &choice); gc
        } while (choice < 1 || choice > 4);

        switch (choice) {
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
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (1);

    return 0;
}