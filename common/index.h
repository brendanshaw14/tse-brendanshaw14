/* index.h- a c header file for the index.c module that provides an index structure. 
    The structure: holds a hashtable of word keys paired to counter items that,
    for each word, hold a set of counters that pair doc id's to the number of
    times that the word appears in that page.

Author: Brendan Shaw, CS50- Winter 2023

Compile: use `make` in the indexer directory to compile indexer and common library,
    or use `make` within the common library to compile the common lib (including index). 

*/

//includes
#include <stdlib.h>
#include <stdio.h>


//the structure
typedef struct index index_t;

typedef struct index {
    hashtable_t* wordIndex;
}  index_t;


/**************** index_new ****************/
/* Create a new index structure with the specified numeber of spots
 *
 * Caller provides:
 *  integer number of slots to create in the hashtable (each spot holds a word) 
 * We do:
 *   if num_slots isn't >0, do nothing.
 *   otherwise, create a new index with a word hashtable that stores num_slots slots
 * Caller is responsible for: 
 *   freeing memory by calling `index_delete` after use
 * Notes:
 *  This function doesn't initialize the counters, it only initializes the index and its hashtable
 */
index_t* index_new(const int num_slots);

/**************** index_save ****************/
/* Saves a word to the index
 *
 * Caller provides:
 *  valid pointer to an index
 *  valid word
 *  valid docID
 * We do:
 *   if the word is already in the index, search its counters for the doc id
 *      if the docID exists, increment it. 
 *      if it doesn't, initialize it with value of 1.  
 */
void index_save(index_t* index, const char* word, const int docID);


/**************** index_delete ****************/
/* Delete the specified index structure
 *
 * Caller provides:
 *  Valid pointer to an index structure
 * We do:
 *  Iterate through the entire index and then iterating through the counters at each word,
 *  deleting the counters, then the words, and finally the index struct itself. 
 * Notes:
 *  This function relies upon the hashtable_delete function calling the counters_delete funciton to work. */
void index_delete(index_t* index);


/**************** index_print ****************/
/* Print out the entire existing index in the correct format to the given file
 *
 * Caller provides:
 *  Valid file pointer (location to print the index to)
 *  Valid index structure. 
 * We do:
 *   Iterate through every word in the hashtable, then print the word
 *      For each one of those words, iterate through its counters and print them
 *      Go to next line for the next word
 *   otherwise, create a new index with a word hashtable that stores num_slots slots
 * Notes:
 *  This function relies on two helper functions within the index.c program:
 *      iterate_helper: this function is passed to the hashtable_iterate function to be applied to each item
 *          it prints the current word to the file and then calls counters iterate with the second helper function
 *      index_printLine: this function is passed to counters_iterate by the iterate_helper to print (with a space in between)
 *          the counters's docID and number of occurences sequentially for every word. 
 *    These functions are not accessible outside of the program and are thus not included in the header file.
 */
void index_print(index_t* index, FILE* fp);