#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define hash_size 100
#define gc getchar();

struct tnode{
    char plate[100];
    char name[100];
    char ID[5];
    tnode* next;
}*arr[hash_size];

void printMenu(){
    puts("Parking System");
    puts("===============");
    puts("1. ADD");
    puts("2. VERIFY");
    puts("3. VIEW");
    puts("4. REMOVE");
    puts("5. EXIT");
    printf("Input : ");
}

int hash(char *plate){
    int key = 0;

    for(int i = 0; i < strlen(plate); i++){
        key += plate[i];
    }

    key *= key;
    
    char temp[100];
    sprintf(temp, "%d", key);

    if(strlen(temp)%2==0){
        char loc[3] = {plate[strlen(plate)/2-1], plate[strlen(plate)/2], '\0'};

        key = atoi(loc);

        return key % hash_size;
    }
    else{
        char loc[3] = {plate[strlen(plate)/2-1], '\0'};
        
        key = atoi(loc);

        return key % hash_size;
    }
}

void push(char *plate, char *name, char *Id){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    int index = hash(plate);
    printf("%d ", index);
    strcpy(c->name, name);
    strcpy(c->plate, plate);
    strcpy(c->ID, Id);
    c->next = NULL;

    if(arr[index] == NULL){
        arr[index] = c;
    }
    else{
        tnode* temp = arr[index];
        while(temp->next){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

void add(){
    char plate[100];
    char name[100];
    char ID[6];

    printf("Enter License plate : ");
    scanf("%s", plate); gc

    printf("Enter Owner Name : ");
    scanf("%s", name); gc;

    for(int i = 0; i <= 5; i++){
        if(i == 5){
            ID[i] = '\0';
            break;
        }
        int choice = rand()%2 + 0;

        if(choice == 0){
            char capital = rand()%26 + 'A'; 
            ID[i] =  capital;
        }
        else if(choice == 1){
            char lower =  rand()%26 + 'a';
            ID[i] = lower;
        }
        else{
            char number = rand()%10 + '0';
            ID[i] = number;
        }
    }

    push(plate, name, ID);
    printf("Parking succesfully!\n");
    printf("Your Parking code : %s\n", ID);
}

void verify(){
    char ID[6] = {};

    printf("Enter Parking code : ");
    scanf("%s", ID); gc;

    for(int i = 0; i < hash_size; i++){
        if(arr[i] == NULL){
            continue;
        }
        else{
            tnode* temp = arr[i];
            int flag = 0;
            while(temp){
                if(strcmp(ID, temp->ID)==0){
                    printf("Vehicle : %s\nOwner : %s\n", temp->plate, temp->name);
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            if(flag == 0) printf("Error");
        }
    }
}

void view(){
    for(int i = 0; i < hash_size; i++){
        if(arr[i] == NULL){
            continue;
        }
        else{
            tnode* temp = arr[i];
            while(temp){
                printf("%s %s %s\n", temp->plate, temp->name, temp->ID);
                temp = temp->next;
            }
        }
    }
}

void remove(){
    char ID[5];

    printf("Enter Parking code : ");
    scanf("%s", ID); gc;

    for(int i = 0; i < hash_size; i++){
        if(arr[i] == NULL){
            continue;
        }
        else{
            tnode* temp = arr[i];
            int flag = 0;
            if(strcmp(temp->ID, ID)==0){
                printf("Vehicle %s has exited\n", temp->plate);
                arr[i] = temp->next;
                free(temp);
                flag = 1;
                break;
            }
            else{
                tnode* temp2 = temp->next;
                while(temp2 != NULL && strcmp(temp2->ID, ID)!= 0){
                    temp = temp2;
                    temp2 = temp2->next;
                }
                printf("Vehicle %s has exited\n", temp2->plate);
                temp->next = temp2->next;
                free(temp2);
                flag = 1;
                break;
            }
            if(flag == 0) printf("Error");
        }
    }
}

int main(){
    srand(time(NULL));
    int choice = -1;
    do{
        do{
            printMenu();
            scanf("%d", &choice); gc
        }while(choice < 0 && choice > 5);

        switch (choice){
            case 1: 
                add();
                break;
            case 2:
                verify();
                break;
            case 3:
                view();
                break;
            case 4:
                remove();
                break;
            case 5: 
                printf("Exiting Program\n");
                return 0 ;
        }
    }while(1);

    return 0;
}