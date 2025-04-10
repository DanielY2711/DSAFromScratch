#include <stdio.h>
#include "util.h"
#include "HashFunction.h"

static int alphabet_size = 26;
static size_t char_size = sizeof(char);


int charToNum(char input){
    return (int)(input - 'A');
}



/*
H(S) = a^s + sigma[i=0; i <= s-1](a^(s-(i+1)) * char(s[i]) % m)
s = len of string
s[i] = char at pos i in string
a = alphabet size (maybe like character space)
char(s) function that maps character to a unqieu code (ASCII)

*/
int hash_String(char* string, int hashspace_size){

    int string_length = slen(string);
    int hashed_string = 0; 

    int multiplier = 1;

    for (int i = string_length - 1; i > -1; --i){
        //printf("stage multi: %i %i\n", multiplier, i);
        int char_code = charToNum(string[i]);
        int result = (multiplier * char_code) % hashspace_size;
        hashed_string = (hashed_string + result) % hashspace_size; 
        multiplier =(multiplier * alphabet_size) % hashspace_size; 
    }

    //printf("final multi: %i\n", multiplier);
    hashed_string = (hashed_string + multiplier) % hashspace_size; 

    return hashed_string; 
}


// int main(){
//     printf("fart:%i\n", hash_String("fart", 1009));
//     printf("shart:%i\n", hash_String("shart", 1009));

//     printf("fartt:%i\n", hash_String("fartt", 1009));
//     return 0;
// }