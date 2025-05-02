#include <stdlib.h>

typedef struct vector_index_data{
    void* data;
    size_t size;
} vector_index_data;

typedef struct vector{
    size_t vector_size;
    vector_index_data** index; 
} vector;


void vector_put_data(vector* vector, size_t ind, void* data, size_t data_size);
void vector_append(vector* vector, void* data, size_t data_size);

vector* init_vector(size_t initial_size);
void destroy_vector(vector* vector);