/* word.c- a c module to normalize a word;

Author: Brendan Shaw, CS50- Winter 2023

Compile: use `make` to compile indexer and common library within the indexer directory, 
    or `make` within the common directory to make the module directly

see word.h for more information */

//includes
#include "string.h"
#include "../libcs50/mem.h"
#include <stdio.h>
#include <ctype.h>

//declaration
char* word_normalize(char* word);


//convert the word to lower case
char* word_normalize(char* word){
    //get length
    int wordLength = strlen(word);
    //make a char* to copy into 
    char* normalizedWord = mem_malloc(strlen(word)+1);
    //loop thorugh chars
    for (int i = 0; i < wordLength; i ++){
       char currentChar = word[i];
       //change to lowercase
       currentChar = tolower(currentChar);
       normalizedWord[i] = currentChar;
    }
    normalizedWord[wordLength] = '\0';
    return normalizedWord;
}
