/*Word.C:
 Module to normalize a word
*/

#include "string.h"
#include "../libcs50/mem.h"
#include <stdio.h>
#include <ctype.h>

char* word_normalize(char* word);


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
