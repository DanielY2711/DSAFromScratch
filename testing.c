#include <stdio.h>
#include <stdlib.h>


void somefunc(void* val){
    return; 
}

int main() {
    somefunc((void*)&10);
    return 0; 
}
