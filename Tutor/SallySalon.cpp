#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

struct node{
	char name[101]; 
	int price; 
	char cate[20]; 
	char avail[20]; 
	int height; 
	node* left; 
	node* right; 
}*Node = NULL; 

int count = 0; 

node* createNode(char* name, int price, char* cate, char* avail){
	node* newNode = (node*)malloc(sizeof(node)); 
	strcpy(newNode->name, name); 
	strcpy(newNode->cate, cate); 
	strcpy(newNode->avail, avail); 
	newNode->price = price; 
	newNode->height = 1; 
	newNode->left = NULL; 
	newNode->right = NULL; 
	return newNode; 
}

void enterCont(){
	printf("Press enter to continue...\n"); 
	getchar(); 
}

int max(int a, int b){
	return a > b ? a : b; 
}

int height(node* root){
	if(root == NULL) return 0; 
	return root->height; 
}

int getBalanceFactor(node* root){
	if(root == NULL) return 0; 
	return height(root->left) - height(root->right); 
}

node* leftRotate(node* x){
	node* y = x->right; 
	node* z = y->left; 
	
	y->left = x; 
	x->right = z; 
	
	x->height = max(height(x->left), height(x->right)) + 1; 
	y->height = max(height(y->left), height(y->right)) + 1; 
	
	return y; 
}

node* rightRotate(node* x){
	node* y = x->left; 
	node* z = y->right; 
	
	y->right = x; 
	x->left = z; 
	
	x->height = max(height(x->left), height(x->right)) + 1; 
	y->height = max(height(y->left), height(y->right)) + 1; 
	
	return y; 
}

int validationName(char* name){
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

node* insertAVL(node* root, node* newNode){
	if(root == NULL) return newNode; 
	else if(strcmp(root->name, newNode->name) > 0) root->left = insertAVL(root->left, newNode); 
	else if(strcmp(root->name, newNode->name) < 0) root->right = insertAVL(root->right, newNode); 
	else return root; 
	
	root->height =  max(height(root->left), height(root->right)) + 1; 
	int balance = getBalanceFactor(root); 
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root); // left left 
		else{
			root->left = leftRotate(root->left); // left right 
			return rightRotate(root); 
		}
	}
	if(balance < -1){
		if(getBalanceFactor(root->right) <= 0) return leftRotate(root); // right right 
		else{
			root->right = rightRotate(root->right); // right left 
			return leftRotate(root); 
		}
	}
	return root; 
}

node* deleteAVL(node* root, char* name){
	if(root == NULL) return NULL; 
	else if(strcmp(root->name, name) > 0) root->left = deleteAVL(root->left, name); 
	else if(strcmp(root->name, name) < 0) root->right = deleteAVL(root->right, name); 
	else{
		if(root->left == NULL && root->right == NULL){
			free(root); 
			return NULL;  
		}
		else if(root->left == NULL || root->right == NULL){
			node* temp = root->left ? root->left : root->right; 
			free(root); 
			return temp; 
		}
		else{ // root->left != NULL && root->right != NULL 
			node* temp = root->left; 
			
			while(temp->right){
				temp = temp->right; 
			}
			
			// copas nilai predecessor 
			strcpy(root->name, temp->name); 
			strcpy(root->cate, temp->cate); 
			strcpy(root->avail, temp->avail); 
			root->price = temp->price; 
			
			root->left = deleteAVL(root->left, temp->name);  
		}
	}
	
	root->height =  max(height(root->left), height(root->right)) + 1; 
	int balance = getBalanceFactor(root); 
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root); // left left 
		else{
			root->left = leftRotate(root->left); // left right 
			return rightRotate(root); 
		}
	}
	if(balance < -1){
		if(getBalanceFactor(root->right) <= 0) return leftRotate(root); // right right 
		else{
			root->right = rightRotate(root->right); // right left 
			return leftRotate(root); 
		}
	}
	return root; 
}

node* insert(node* root){
	system("clear"); 
	
	char name[101], cate[20], avail[20]; 
	int price; 
	
	do{
		printf("insert name: "); 
		scanf("%[^\n]", name); getchar(); 
	} while(validationName(name) == -1); 
	
	do{
		printf("insert price [50.000 - 1.000.000]: "); 
		scanf("%d", &price); getchar(); 
	} while(price < 50000 || price > 1000000); // inclusive 
	
	do{
		printf("insert category [Hair Care | Nail Care | Body Care]: "); 
		scanf("%[^\n]", cate); getchar(); 
	} while(strcmp(cate, "Hair Care") != 0  && strcmp(cate, "Nail Care") != 0 &&
			strcmp(cate, "Body Care") != 0); // case sensitive 
			
	do{
		printf("insert availability: "); 
		scanf("%s", avail); getchar(); // case sensitive 
	} while(strcmp(avail, "Available") != 0 && strcmp(avail, "Unavailable") != 0); 
	
	node* newNode = createNode(name, price, cate, avail); 
	root = insertAVL(root, newNode); 
	
	printf("[New Treatment is Successfully Inserted]\n"); 
	enterCont(); 
	
	return root; 
}

void preOrder(node* root){
	if(root != NULL){
		printf("Treatment   : %s\n", root->name); 
		printf("Price       : %d\n", root->price); 
		printf("Category    : %s\n", root->cate); 
		printf("Availablity : %s\n", root->avail); 
		
		preOrder(root->left); 
		preOrder(root->right); 
	}
}

void inOrder(node* root){
	if(root != NULL){		
		inOrder(root->left); 
		
		printf("Treatment   : %s\n", root->name); 
		printf("Price       : %d\n", root->price); 
		printf("Category    : %s\n", root->cate); 
		printf("Availablity : %s\n", root->avail); 
		
		inOrder(root->right); 
	}
}

void postOrder(node* root){
	if(root != NULL){		
		postOrder(root->left); 		
		postOrder(root->right); 
		
		printf("Treatment   : %s\n", root->name); 
		printf("Price       : %d\n", root->price); 
		printf("Category    : %s\n", root->cate); 
		printf("Availablity : %s\n", root->avail); 
	}
}

void view(node* node){
	system("clear"); 
	if(node == NULL){
		printf("no data\n"); 
		return; 
	}
	
	char input[10]; 
	
	do{
		printf("insert view mode [pre | in | post]: "); 
		scanf("%s", input); getchar(); 
	} while(strcmp(input, "pre") != 0 && strcmp(input, "in") != 0 && 
		strcmp(input, "post") != 0); 
		
	if(strcmp(input, "pre") == 0) preOrder(node); 
	else if(strcmp(input, "in") == 0) inOrder(node); 
	else postOrder(node);  
	
	enterCont(); 
}

int alreadyInTree(node* root, char* name){
	if(root == NULL) return -1; 
	if(strcmp(root->name, name) == 0) return 1; 
	
	int leftSide = alreadyInTree(root->left, name); 
	if(leftSide == 1) return 1; 
	return alreadyInTree(root->right, name);  
}

node* del(node* root){
	system("clear"); 
	if(root == NULL){
		printf("no data\n"); 
		enterCont(); 
		return root; 
	}
	
	char name[101]; 
	
	printf("DELETE TREATMENT\n"); 
	printf("insert name to be deleted: "); 
	scanf("%[^\n]", name); getchar(); 
	
	if(alreadyInTree(root, name) == 1){ // data ancur kalo data gaada di tree
		root = deleteAVL(root, name); 
		printf("[Data successfully deleted]\n"); 
		count--; 
	}
	else{
		printf("Data does not exist!\n"); 
	}
	enterCont(); 
	
	return root; 
}

int main(){
	int choice = -1; 
	
	do{
		do{
			printf("Sally Salon\n"); 
			printf("======================\n"); 
			printf("Menu:\n"); 
			printf("1. View Available Treatment\n"); 
			printf("2. Insert New Treatment\n"); 
			printf("3. Delete Treatment\n"); 
			printf("4. Exit\n"); 
			printf("[1-4]\n"); 
			printf(">> "); 
			scanf("%d", &choice); getchar(); 
			
		} while(choice < 1 || choice > 4); 
		
		switch(choice){
			case 1: 
				view(Node); 
				break; 
			case 2: 
				Node = insert(Node); 
				count++; 
				break; 
			case 3: 
				Node = del(Node); 
				break; 
			case 4: 
				return 0; 
		}
	} while(1); 
	return 0; 
}