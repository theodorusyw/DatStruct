#include <stdio.h>

int main(){
    int a = 10;
    int* ptr = &a;
    *ptr = 50;
    printf("memory dari ptr: %d\n", &ptr);
    printf("value dari ptr: %d\n", ptr);
    printf("value dari memory yang disimpan: %d\n", *ptr);
    return 0;
}