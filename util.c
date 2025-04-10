#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "util.h"
#include <assert.h>
int computeMaxPrime(int x){
    
    void *ptr = malloc(x);

    assert(ptr != NULL);

    memset(ptr, 0, x);

    int last_prime = 2; 
    //printf("Starting loop\n");
    for (int i = 2; i < x; ++i){
        unsigned char* temp_ptr = (unsigned char*) ptr; 
        temp_ptr += i;
        unsigned char byte = *temp_ptr;
        if ((byte | 0) == 0){
            last_prime = i;
            //printf("new last prime: %i\n", last_prime);
            
            int j = i;
            while (j < x & j > 0){
                *temp_ptr = 1;
                temp_ptr += i; 
                j += i;
            }
        }
    }
    

    free(ptr);

    return last_prime; 
}

int slen(char* ptr){
    int l = 0;

    while (ptr[l] != '\0'){
        l++;
    }
    return l; 
}

void copy_memory(unsigned char* origin, unsigned char* destination, size_t data_size){
    assert(origin != NULL && destination != NULL);
    for (size_t i = 0; i < data_size; ++i){
        destination[i] = origin[i];
    }
}