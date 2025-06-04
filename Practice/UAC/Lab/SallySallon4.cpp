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

    if (balance < -1) {
        if (getBalance(root->left) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root);
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
            return temp;
        } else {
            Node* temp = root->left;

            while (temp->right) {
                temp = temp->right;
            }

            strcpy(root->name, temp->name);
            root->price = temp->price;
            strcpy(root->cate, temp->cate);
            strcpy(root->avail, temp->avail);

            root->left = deleteAVL(root->left, temp->name);
        }
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

    if (balance < -1) {
        if (getBalance(root->left) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root);
            return rotateLeft(root);
        }
    }

    return root;
}

Node* insertMenu(Node* root) {
    char name[101];
    int price;
    char cate[101];
    char avail[101];

    do {
        printf("Insert Name : ");
        scanf("%[^\n]", name); gc
    } while (validName(name) == -1);

    do {
        printf("Insert Price [50.000 - 1.000.000] : ");
        scanf("%d", &price); gc
    } while (price < 50000 || price > 1000000);

    do {
        printf("Insert Category [Hair Care | Nail Care | Body Care] : ");
        scanf("%[^\n]", cate); gc
    } while (strcmp(cate, "Hair Care") != 0 && strcmp(cate, "Nail Care") != 0 && strcmp(cate, "Body Care") != 0);

    do {
        printf("Insert Available [Available | Unavailable] : ");
        scanf("%s", avail); gc
    } while (strcmp(avail, "Available") != 0 && strcmp(avail, "Unavailable") != 0);

    Node* newNode = createNode(name, price, cate, avail);
    root = insertAVL(root, newNode);
    count++;

    puts("Succesfull");
    enterToContinue();

    return root;
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf("================================\n");
        printf("Treatment   : %s\n", root->name);
        printf("Price       : %d\n", root->price);
        printf("Category    : %s\n", root->cate);
        printf("Availablity : %s\n", root->avail);
        printf("================================\n");

        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("================================\n");
        printf("Treatment   : %s\n", root->name);
        printf("Price       : %d\n", root->price);
        printf("Category    : %s\n", root->cate);
        printf("Availablity : %s\n", root->avail);
        printf("================================\n");

        inOrder(root->right);
    }
}
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);

        printf("================================\n");
        printf("Treatment   : %s\n", root->name);
        printf("Price       : %d\n", root->price);
        printf("Category    : %s\n", root->cate);
        printf("Availablity : %s\n", root->avail);
        printf("================================\n");
    }
}

void viewMenu(Node* root) {
    if (root == NULL) {
        puts("There is no data!");
        enterToContinue();
        return;
    }

    char input[10];
    do {
        printf("Insert View Mode [PreOrder | InOrder | PostOrder] : ");
        scanf("%s", input); gc
    } while (strcmp(input, "PreOrder") != 0 && strcmp(input, "InOrder") != 0 && strcmp(input, "PostOrder") != 0);
    
    if (strcmp(input, "PreOrder") == 0) {
        preOrder(root);
    } else if (strcmp(input, "InOrder") == 0) {
        inOrder(root);
    } else {
        postOrder(root);
    }
    
    enterToContinue();
}

int alreadyInTree(Node* root, char* name) {
    if (root == NULL) {
        return -1;
    }

    if (strcmp(root->name, name) == 0) {
        return 1;
    }

    int leftSide = alreadyInTree(root->left, name);
    if (leftSide == 1) {
        return 1;
    }

    return alreadyInTree(root->right, name);
}

Node* deleteMenu(Node* root) {
    if (root == NULL) {
        puts("No Data");
        enterToContinue();
        return root;
    }

    char name[101];

    printf("Insert name : ");
    scanf("%[^\n]", name); gc

    if (alreadyInTree(root, name) == 1) {
        root = deleteAVL(root, name);
        puts("Succesfull");
        count--;
    } else {
        puts("Not Found");
    }

    enterToContinue();

    return root;
}

int main() {
    int choice = -1;

    do {
        do {
            system("clear");
            puts("==============");
            puts("Sally Salon");
            puts("==============");
            puts("1. Insert Menu");
            puts("2. View Menu");
            puts("3. Delete Menu");
            puts("4. Exit");
            puts("==============");
            printf(">> ");
            scanf("%d", &choice); gc
        } while(choice < 1 || choice > 4);

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
            puts("Exiting...");
            return 0;
        default:
            puts("Invalid choice, please try again");
            break;
        }
    } while(1);
    return 0;
}