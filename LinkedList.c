#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void test(){
    printf("Test Works \n");
    return; 
}


void allocateAndDeallocate(void* value, size_t value_size){
    printf("Given adress: %p\n", value);
    void* stored_data = malloc(value_size);
    if (stored_data == NULL){
        printf("ERROR WITH ALLOCATION\n");
    }
    printf("New adress: %p\n", stored_data);
    printf("Before storing %d\n", (int*)stored_data);
    memmove(stored_data, value, value_size); 

    printf("Same as above: %p\n", stored_data);
    printf("Stored value %d\n", *(int*)stored_data);
    int newvar = *(int*)stored_data;

    free(stored_data);
    
}

int main(){
    int x = 50; 
    allocateAndDeallocate(&x, sizeof(x));
    return 0;
}