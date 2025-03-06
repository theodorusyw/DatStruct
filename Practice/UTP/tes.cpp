#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void printMenu(){
    puts("+-------------------+");
    puts("| Hotel GrAsylvania |");
    puts("+-------------------+");
    puts("1. Tes");
    puts("2. Tes");
    puts("3. Tes");
    puts("4. Tes");
    puts("5. Tes");
}


int main(){
    int choices;
    do{
        printMenu();
        printf(">> ");
        scanf("%d", &choices);

        switch (choices){
            case 1:
            break;

            case 2:
            break;

            case 3:
            break;

            case 4:
            break;

            case 5:
            return 0;
            
        }
    }
    while(1);
}

