/*Header file for Word.C

word: a module that implements a function to normalize (convert to lowercase)
a word.

Author: Brendan Shaw: CS50- Winter 2023

*/

//includes
#include "string.h"
#include <stdio.h>
#include <ctype.h>


/**************word_normalize***********/
/* Normalize the given word
 *
 * Caller provides:
 *   A valid char* word 
 * We return:
 *   Char* pointer to the normalized word
 *
 * Caller is responsible for:
 *   later freeing the returned char* from memory 
 * */
char* word_normalize(char* word);