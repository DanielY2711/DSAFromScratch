#include "vector.h"
#include <stdlib.h>
#include <stdio.h>



typedef struct heap_struct{
    size_t next_position;
    vector* data_vector;

} heap_struct;

void print_heap(heap_struct* heap);

void heap_destroy(heap_struct* heap){
    destroy_vector(heap->data_vector);
    free(heap);
}; 

heap_struct* heap_init(){
    heap_struct* new_heap = malloc(sizeof(heap_struct));
    new_heap->data_vector = init_vector(0);
    new_heap->next_position = 0;
}


void heap_insert(heap_struct* heap, int value){
    /*
    Either the vector already has space or not for the value that needs to be inserted
    */
    if (heap->data_vector->vector_size == heap->next_position){
        vector_append(heap->data_vector, &value, sizeof(int));
    }  
    else{
        vector_put_data(heap->data_vector, heap->next_position, &value, sizeof(int));
    }
    // Bubbling up
    size_t current_position = heap->next_position;
    int temp = -1;
    while (current_position != 0 && *(int*)(heap->data_vector->index[current_position]->data) < *(int*)(heap->data_vector->index[(current_position - 1)/2]->data)){
        temp = *(int*)(heap->data_vector->index[current_position]->data);
        *(int*)(heap->data_vector->index[current_position]->data) = *(int*)(heap->data_vector->index[(current_position - 1)/2]->data);
        *(int*)(heap->data_vector->index[(current_position - 1)/2]->data) = temp; 
        current_position = (current_position - 1) / 2; 
    }
    heap->next_position++; 
    print_heap(heap);
}

int heap_pop(heap_struct* heap){
    if (heap->next_position == 0){
        printf("Tried popping from empty heap\n");
        return -1;
    }

    int returned_value = *(int*)(heap->data_vector->index[0]->data);
    
    //Heap may become empty
    if (heap->next_position == 1){
        heap->next_position--;
        return returned_value;
    }

    // Swap with last value
    *(int*)(heap->data_vector->index[0]->data) = *(int*)(heap->data_vector->index[heap->next_position-1]->data);
    heap->next_position--;

    /*
    compare current position to the children nodes
    */
    size_t current_position = 0; 
    vector_index_data** heap_data = heap->data_vector->index; 
    while (
    (current_position*2 + 1 < heap->next_position && *(int*)(heap_data[current_position]->data) > *(int*)(heap_data[current_position*2+1]->data)) 
    || 
    (current_position*2 + 2 < heap->next_position && *(int*)(heap_data[current_position]->data) > *(int*)(heap_data[current_position*2+2]->data))
    )
    {
        if (current_position*2 + 2 < heap->next_position && *(int*)(heap_data[current_position*2 + 2]->data) > *(int*)(heap_data[current_position*2+1])->data){
            int temp = *(int*)(heap_data[current_position]->data);
            *(int*)(heap_data[current_position]->data) = *(int*)(heap_data[current_position*2+1])->data;
            *(int*)(heap_data[current_position*2+1])->data = temp;
            current_position = current_position*2 + 1;
        }
        else{
            int temp = *(int*)(heap_data[current_position]->data);
            *(int*)(heap_data[current_position]->data) = *(int*)(heap_data[current_position*2+2])->data;
            *(int*)(heap_data[current_position*2+2])->data = temp;
            current_position = current_position*2 + 2;
        }
    }

    return returned_value;
}

void print_heap(heap_struct* heap){
    printf("[");
    for (size_t i = 0; i < heap->next_position; ++i){
        printf("%i, ", *(int*)(heap->data_vector->index[i]->data));
    }
    printf("]\n");
}

int main(){
    heap_struct* myHeap = heap_init();

    heap_insert(myHeap, 10);
    heap_insert(myHeap, 9);
    heap_insert(myHeap, 8);
    heap_insert(myHeap, 7);
    heap_insert(myHeap, 6);
    heap_insert(myHeap, 5);
    heap_insert(myHeap, 4);
    heap_insert(myHeap, 3);
    heap_insert(myHeap, 2);
    heap_insert(myHeap, 1);


    
    print_heap(myHeap); 

    while (myHeap->next_position != 0){
        printf("Popped: %i\n", heap_pop(myHeap)); 
        print_heap(myHeap); 
    }

    heap_pop(myHeap);

    heap_destroy(myHeap);

}

