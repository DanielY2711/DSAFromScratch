#include "HashFunction.h"
#include <stdlib.h>
#include "util.h"
#include <stdio.h>
#include <assert.h>

static size_t adr_size = sizeof(void*);
static size_t oa_slot_size = sizeof(void*) * 2;


typedef struct HOAPair{
    void* val;
    size_t val_size;
    char* key;
} HOAPair; 

typedef struct HashMapOA
{
    size_t hashmap_size; 
    HOAPair** data;
    void** del;
} HashMapOA;


HashMapOA* init_HashMap_OA(size_t hashmapSize){
    HashMapOA* HashMap = malloc(sizeof(HashMapOA));
    HashMap->hashmap_size = hashmapSize;
    HashMap->data = malloc(adr_size * hashmapSize);
    
    for (int i = 0; i < hashmapSize; ++i){
        HashMap->data[i] = NULL; 
    }

    HashMap->del = malloc(sizeof(void*));
    return HashMap;
}

void destroy_HashMap_OA(HashMapOA* HashMap){

    // Scour the map for all allocated keys and value adresses
    for (size_t i = 0; i < HashMap->hashmap_size; ++i){
        if (HashMap->data[i] != NULL && HashMap->data[i] != HashMap->del){
            free(HashMap->data[i]->key);
            free(HashMap->data[i]->val);
            free(HashMap->data[i]);
        }
    }
    free(HashMap->data);
    free(HashMap->del);
    free(HashMap);

    return; 
}

void add_Element_HashMap_OA(HashMapOA* HashMap, char* key, void* value, size_t value_size){
    int hash_value = hash_String(key, HashMap->hashmap_size);
    
    size_t slot = hash_value; 

    while (slot < HashMap->hashmap_size && HashMap->data[slot] != 0 && HashMap->data[slot] != HashMap->del && !(str_compare(HashMap->data[slot]->key, key))){
        slot++; 
    }

    if (slot >= HashMap->hashmap_size){
        printf("Hashmap size exceeded\n");
        return; 
    }

    
    // Found a valid slot so now we can store the value
    // Take space for the struct, or free and reaallocate for the new value
    if (HashMap->data[slot] == 0 || HashMap->data[slot] == HashMap->del){

        HashMap->data[slot] = malloc(sizeof(HOAPair));
        HashMap->data[slot]->key = malloc(slen(key) + 1);
        copy_memory(key, HashMap->data[slot]->key, slen(key) + 1); 
    }
    else{
        /*
        The key has been recorded before so the value space needs to be freed
        This is necessary in case the allocation size for the value has changed
        */ 
        free(HashMap->data[slot]->val);
    }

    // Set val size
    HashMap->data[slot]->val_size = value_size;
    // Allocate space for the value
    HashMap->data[slot]->val = malloc(value_size);


    copy_memory(value, HashMap->data[slot]->val, value_size);
}

int main(){
    HashMapOA* myMap = init_HashMap_OA(2);
    int x = 10;
    int y = 15; 
    add_Element_HashMap_OA(myMap, "fart", &x, sizeof(int)); 
    add_Element_HashMap_OA(myMap, "fart", &y, sizeof(int)); 
    destroy_HashMap_OA(myMap);

    return 0; 
}