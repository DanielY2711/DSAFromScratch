#include "HashFunction.h"
#include <stdlib.h>
#include "util.h"
#include <stdio.h>

static size_t adr_size = sizeof(void*);
static size_t oa_slot_size = sizeof(void*) * 2;


typedef struct HashMapOA
{
    int hashmap_size; 
    void** data;
    void** del;
} HashMapOA;


HashMapOA* init_HashMap_OA(int hashmapSize){
    HashMapOA* HashMap = malloc(sizeof(HashMapOA));
    HashMap->hashmap_size = hashmapSize;
    HashMap->data = malloc(oa_slot_size * hashmapSize);
    
    for (int i = 0; i < hashmapSize * 2; ++i){
        *(HashMap->data + i) = NULL; 
    }

    HashMap->del = malloc(sizeof(void*));
    return HashMap;
}

void destroy_HashMap_OA(HashMapOA* HashMap){

    // Scour the map for all allocated keys and value adresses
    void** current_adr = HashMap->data;
    for (size_t i = 0; i < HashMap->hashmap_size*2; ++i){
        if (HashMap->data[i] != NULL && HashMap->data[i] != HashMap->del){
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
    
    void** slot = HashMap->data + hash_value * 2;
    void** limit = HashMap->data + HashMap->hashmap_size*2;
    while (slot < limit && *slot != 0 && *(int*)*slot != hash_value && *slot != HashMap->del){
        slot++; 
    }

    if (slot >= limit){
        printf("Hashmap size exceeded\n");
        return; 
    }

    void** key_adr = slot;
    void** val_adr = slot + 1; 
    // Found a valid slot so now we can store the value
    // Take space for key, unless already allocated
    if (*slot == 0 || *slot == HashMap->del){
        *key_adr = malloc(sizeof(int));
        *(int*)*key_adr = hash_value; 
    }
    else{
        /*
        The key has been recorded before so the value space needs to be freed
        This is necessary in case the allocation size for the value has changed
        */ 
        free(*val_adr);
    }

    // Allocate space for the value
    void* value_store = malloc(value_size);

    *val_adr = value_store;
    copy_memory(value, value_store, value_size);
    
}

int main(){
    HashMapOA* myMap =init_HashMap_OA(5);
    int x = 10;
    int y = 15; 
    add_Element_HashMap_OA(myMap, "fart", &x, sizeof(int)); 
    add_Element_HashMap_OA(myMap, "fart", &y, sizeof(int)); 
    destroy_HashMap_OA(myMap);
    return 0; 
}