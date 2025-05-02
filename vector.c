#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "assert.h"
#include "vector.h"






vector* init_vector(size_t initial_size){
    vector* new_vector = malloc(sizeof(vector));
    new_vector->index = malloc(sizeof(void*) * initial_size);
    new_vector->vector_size = initial_size; 

    // 0-initialize all the indexes
    for (size_t i = 0; i < new_vector->vector_size; ++i){
        new_vector->index[i] = NULL; 
    }

    return new_vector;
}

void destroy_vector(vector* vector){


    for (size_t i = 0; i < vector->vector_size; ++i){
        if (vector->index[i] != NULL){
            free(vector->index[i]->data);
            free(vector->index[i]);
        }
    }

    free(vector);

    return; 
}

void vector_put_data(vector* vector, size_t ind, void* data, size_t data_size){

    if (ind >= vector->vector_size){
        printf("Out of bounds query\n");
        return; 
    }

    // Free previous data if exists
    if (vector->index[ind] != NULL){
        free(vector->index[ind]->data);
    }
    else{
        vector->index[ind] = malloc(sizeof(vector_index_data));
    }
    vector->index[ind]->size = data_size; 
    vector->index[ind]->data = malloc(data_size);

    copy_memory(data, vector->index[ind]->data, data_size);

    return; 
}


void vector_append(vector* vector, void* data, size_t data_size){
    // Allocate the needed space
    vector->index = realloc(vector->index, (vector->vector_size + 1) * sizeof(void*));

    // Add the data
    vector->index[vector->vector_size] = malloc(sizeof(vector_index_data));
    vector->index[vector->vector_size]->size = data_size;
    vector->index[vector->vector_size]->data = malloc(data_size);
    
    copy_memory(data, vector->index[vector->vector_size]->data, data_size);
    vector->vector_size++; 
    
    return; 
}

// int main(){

//     vector* myVec = init_vector(10);

//     assert(myVec->index[1] == NULL);

//     int x = 10;
//     vector_put_data(myVec, 1, &x, sizeof(int));
//     assert(*(int*)(myVec->index[1]->data) == 10);


//     x += 10;
//     vector_put_data(myVec, 2, &x, sizeof(int));
//     assert(*(int*)(myVec->index[2]->data) == 20);

//     x += 9;
//     vector_append(myVec, &x, sizeof(int));
//     assert(*(int*)(myVec->index[10]->data) == 29);
//     assert(*(int*)(myVec->index[2]->data) == 20);

//     char str[] = "fart";
//     vector_append(myVec, &str, slen(str) + 1);
//     printf("%s\n", (char*)(myVec->index[11]->data));
//     assert(str_compare((char*)(myVec->index[11]->data), "fart") == 1);
//     destroy_vector(myVec);

//     return 0;
// }