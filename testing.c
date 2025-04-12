#include <stdio.h>
#include <stdlib.h>


void somefunc(void* val){
    return; 
}

int main() {
    int** series = malloc(sizeof(int) * 5);
    int x = 10;
    series[4] = malloc(sizeof(int)); 
    series[4] = &x; 
    free(series[4]);
    free(series);

    int** ser = malloc(sizeof(int) * 5);

    for (size_t i = 0; i < 5; ++i){
        ser[i] = NULL; 
    }


    return 0; 
}
