#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>

void test(){
    printf("Test Works \n");
    return; 
}


typedef struct LinkedNode{
    struct LinkedNode* previous_Node;
    struct LinkedNode* next_Node;
    void* node_data; 
    size_t data_size;
} LinkedNode;

typedef struct LinkedListStruct{
    LinkedNode* header_Node;
    LinkedNode* tail_Node;
} LinkedListStruct;






LinkedListStruct* InitLinkedList(){
    LinkedListStruct* LinkedList = malloc(sizeof(LinkedListStruct));
    LinkedList->header_Node = NULL;
    LinkedList->tail_Node = NULL; 
}

LinkedNode* InitLinkedNode(void* data, size_t dataSize){
    LinkedNode* NewLinkedNode = malloc(sizeof(LinkedNode));
    NewLinkedNode->node_data = malloc(dataSize);
    NewLinkedNode->data_size = dataSize;
    NewLinkedNode->next_Node = NULL;
    NewLinkedNode->previous_Node = NULL; 
    memmove(NewLinkedNode->node_data, data, dataSize);

    return NewLinkedNode;
}

void insert_LL_End(LinkedListStruct* LinkedList, void* data, size_t dataSize){
    LinkedNode* NewLinkedNode = InitLinkedNode(data, dataSize);
    
    // Empty list
    if (LinkedList->header_Node == NULL){
        assert(LinkedList->tail_Node == NULL);
        LinkedList->header_Node = NewLinkedNode;
        LinkedList->tail_Node = NewLinkedNode;
    }
    else{
        assert(LinkedList->tail_Node != NULL); 
        assert(LinkedList->tail_Node->next_Node == NULL);
        assert(LinkedList->header_Node->previous_Node == NULL);
        LinkedList->tail_Node->next_Node = NewLinkedNode;
        NewLinkedNode->previous_Node = LinkedList->tail_Node;
        LinkedList->tail_Node = NewLinkedNode;
    }

}


void* peek_LL_End(LinkedListStruct* LinkedList){
    if (LinkedList->tail_Node != NULL){
        return LinkedList->tail_Node->node_data;
    }
    return NULL;
}

void pop_LL_End(LinkedListStruct* LinkedList){
    if (LinkedList->tail_Node == NULL){
        return;
    }
    if (LinkedList->tail_Node == LinkedList->header_Node){
        free(LinkedList->header_Node->node_data);
        free(LinkedList->header_Node);
        LinkedList->header_Node= NULL; 
        LinkedList->tail_Node = NULL; 
        printf("Popped last node\n");
        return; 
    }
    LinkedNode* new_Tail_Node = LinkedList->tail_Node->previous_Node;
    new_Tail_Node->next_Node = NULL;
    free(LinkedList->tail_Node->node_data);
    free(LinkedList->tail_Node);
    LinkedList->tail_Node = new_Tail_Node; 
    printf("Popped some node\n"); 
    return; 
}



void insert_LL_Start(LinkedListStruct* LinkedList, void* data, size_t dataSize){ 
    LinkedNode* NewLinkedNode = InitLinkedNode(data, dataSize);
    
    // Empty list
    if (LinkedList->header_Node == NULL){
        assert(LinkedList->tail_Node == NULL);
        LinkedList->header_Node = NewLinkedNode;
        LinkedList->tail_Node = NewLinkedNode;
    }
    else{
        assert(LinkedList->tail_Node != NULL); 
        assert(LinkedList->tail_Node->next_Node == NULL);
        assert(LinkedList->header_Node->previous_Node == NULL);
        LinkedList->header_Node->previous_Node = NewLinkedNode;
        NewLinkedNode->next_Node = LinkedList->header_Node;
        LinkedList->header_Node = NewLinkedNode;
    }
}

void* peek_LL_Start(LinkedListStruct* LinkedList){
    if (LinkedList->header_Node != NULL){
        return LinkedList->header_Node->node_data;
    }
    return NULL;
}


void pop_LL_Start(LinkedListStruct* LinkedList){
    if (LinkedList->tail_Node == NULL){
        return;
    }
    if (LinkedList->tail_Node == LinkedList->header_Node){
        free(LinkedList->header_Node->node_data);
        free(LinkedList->header_Node);
        LinkedList->header_Node= NULL; 
        LinkedList->tail_Node = NULL; 
        printf("Popped last node\n");
        return; 
    }
    LinkedNode* new_Head_Node = LinkedList->header_Node->next_Node;
    new_Head_Node->previous_Node = NULL;
    free(LinkedList->header_Node->node_data);
    free(LinkedList->header_Node);
    LinkedList->header_Node = new_Head_Node; 
    printf("Popped some node\n"); 
    return; 
}
void destroy_LL(LinkedListStruct* LinkedList){
    LinkedNode* currentNode = LinkedList->header_Node;

    while (currentNode != NULL){
        int val = *(int*)currentNode->node_data;
        printf("%d ", val);
        LinkedNode* prevNode = currentNode;
        currentNode = currentNode->next_Node;
        free(prevNode->node_data);
        free(prevNode);
    }

    free(LinkedList);
    printf("end\n");
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


// int main(){

//     LinkedListStruct* myLinkedList = InitLinkedList();

    
//     printf("Initial head and tail pointers %p, %p\n", myLinkedList->header_Node, myLinkedList->tail_Node); 

//     int x = 1;
//     int y = 2;
//     int z = 3;
//     int a = 4;

//     insert_LL_End(myLinkedList, &x, sizeof(x));
//     insert_LL_End(myLinkedList, &y, sizeof(x));
//     insert_LL_Start(myLinkedList, &z, sizeof(x));
//     insert_LL_Start(myLinkedList, &a, sizeof(x));
    
//     pop_LL_Start(myLinkedList);
//     pop_LL_End(myLinkedList);
    

//     destroy_LL(myLinkedList);

//     return 0;
// }