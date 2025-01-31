#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 10

struct Node{
    char name[40];
    Node* next;
} *head[max];

Node* createNewNode(char *name){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

int hash(char *name){
    int key = 0;
    for(int i = 0; i < strlen(name); i++){
        key += name[i];
    }
    return key % max;
}

void push(char *name){
    Node *newNode = createNewNode(name);
    // Calculate hash key
    int pos = hash(name);
    // Push 
    // 1. Ketika head nya kosong
    if(head[pos] == NULL){
        head[pos] = newNode;
        return;
    }
    // 2. Ketika head ada isinya
    Node *temp = head[pos];
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void print(){
    for(int i = 0; i < max; i++){
        Node *temp = head[i];
        printf("%d: ", i);
        while(temp){
            printf("%s -> ", temp->name);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void pop(char *name) {
    int pos = hash(name);
    // Katik head[pos]nya
    if(head[pos] == NULL){
        printf("Gaada bos di hash table!\n");
        return;
    }else{
        if(strcmp(head[pos]->name, name) == 0){
            Node *temp = head[pos];
            head[pos] = temp->next;
            free(temp);
        } else {
            Node *temp = head[pos];
            while(temp->next != NULL && strcmp(temp->next->name, name) != 0){
                temp = temp->next;
            }
            Node *toPop = temp->next;
            temp->next = toPop->next;
            free(toPop);
        }
    }
}

int main(){
    push("budi");
    push("andi");
    push("agus");
    push("neo");
    push("ziva");
    push("jaden");
    push("nana");
    push("webe");
    print();
    return 0;
}