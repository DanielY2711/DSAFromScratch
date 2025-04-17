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

    while (slot < HashMap->hashmap_size && 
        HashMap->data[slot] != 0 && 
        HashMap->data[slot] != HashMap->del && 
        !(str_compare(HashMap->data[slot]->key, key)))
    {
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

size_t find_key_slot_Hashmap_OA(HashMapOA* HashMap, char* key){
    int hash_value = hash_String(key, HashMap->hashmap_size);
    size_t slot = hash_value; 

    while (
        slot < HashMap->hashmap_size && 
        HashMap->data[slot] != 0 && 
        (HashMap->data[slot] == HashMap->del || !(str_compare(HashMap->data[slot]->key, key)))
        )
    {
        slot++; 
    }

    if (slot == HashMap->hashmap_size ||
        HashMap->data[slot] == 0 ||
        HashMap->data[slot] == HashMap->del ||
        !(str_compare(HashMap->data[slot]->key, key))
        )
    {
        printf("Not found\n");
        return HashMap->hashmap_size;
    }
    printf("Found in slot %zu\n", slot);
    return slot;
}

int check_Element_Hashmap_OA(HashMapOA* HashMap, char* key){
    size_t slot = find_key_slot_Hashmap_OA(HashMap, key);
    return slot==HashMap->hashmap_size ? 0 : 1; 
}

HOAPair* get_Element_HashMap_OA(HashMapOA* HashMap, char* key){
    size_t slot = find_key_slot_Hashmap_OA(HashMap, key);
    return slot == HashMap->hashmap_size ? 0 : HashMap->data[slot];
}

void delete_Element_HashMap_OA(HashMapOA* HashMap, char* key){
    size_t slot = find_key_slot_Hashmap_OA(HashMap, key);

    if (slot == HashMap->hashmap_size){
        return;
    }

    HOAPair* pair = HashMap->data[slot];
    free(pair->key);
    free(pair->val);
    free(HashMap->data[slot]);
    HashMap->data[slot] = (HOAPair*)HashMap->del; 
    return; 
}

// int main(){
//     HashMapOA* myMap = init_HashMap_OA(3);
//     int x = 10;
//     int y = 15; 


//     printf("Hashvalues %i, %i\n", hash_String("sartaaaa", 3), hash_String("srtaa",3));
//     add_Element_HashMap_OA(myMap, "sartaaaa", &x, sizeof(int)); 
//     add_Element_HashMap_OA(myMap, "srtaa", &y, sizeof(int)); 
//     assert(check_Element_Hashmap_OA(myMap, "sartaaaa") == 1);
//     assert(check_Element_Hashmap_OA(myMap, "srtaa") == 1);
//     delete_Element_HashMap_OA(myMap, "sartaaaa");
//     assert(check_Element_Hashmap_OA(myMap, "srtaa") == 1);
//     add_Element_HashMap_OA(myMap, "sartaaaa", &x, sizeof(int)); 
//     assert(check_Element_Hashmap_OA(myMap, "sartaaaa") == 1);









//     destroy_HashMap_OA(myMap);
//     return 0; 
// }