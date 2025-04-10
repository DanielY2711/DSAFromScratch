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
    HashMapOA* newHashMap = malloc(sizeof(HashMapOA));
    newHashMap->hashmap_size = hashmapSize;
    newHashMap->data = malloc(oa_slot_size * hashmapSize);
    
    for (int i = 0; i < hashmapSize; ++i){
        *(newHashMap->data + i) = NULL; 
    }

    newHashMap->del = malloc(sizeof(void*));
    return newHashMap;
}

void destroy_HashMap_OA(HashMapOA* HashMap){

    // Scour the map for all allocated keys and value adresses
    void** current_adr = HashMap->data;
    while (current_adr < HashMap->data + oa_slot_size * HashMap->hashmap_size){
        if (*current_adr != NULL){
            /* Issue here, the way we currently store things we lose the size of the value we are storing (which is a void*), need to store the 
            value size somewhere
            also we currenltly store hash values in slots, which is useless since it dosent help us resolve collisions, 
            fix that as well.
            */
            free(**current_adr); 
            printf("freed ptr %p\n", current_adr); 
        }
        current_adr += adr_size; 
    }
    free(HashMap->data);
    free(HashMap->del);
    free(HashMap);

    return; 
}

void add_Element_HashMap_OA(HashMapOA* HashMap, char* key, void* value, size_t value_size){
    int hash_value = hash_String(key, HashMap->hashmap_size);
    
    void** slot = HashMap->data + oa_slot_size * hash_value;
    void** limit = HashMap->data + oa_slot_size * HashMap->hashmap_size;
    while (slot < limit && *slot != 0 && *(int*)*slot != hash_value && *slot != HashMap->del){
        slot += oa_slot_size; 
    }

    if (slot >= limit){
        printf("Hashmap size exceeded\n");
        return; 
    }

    void** key_adr = slot;
    void** val_adr = slot + adr_size; 
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