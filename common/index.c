/* INDEX- a c module to provide an index structure. 
    The structure: holds a hashtable of word keys paired to counter items that,
    for each word, hold a set of counters that pair doc id's to the number of
    times that the word appears in that page.

Author: Brendan Shaw, CS50- Winter 2023

Compile: use `make` in the indexer directory to compile indexer and common library,
    or use `make` within the common library to compile the common lib (including index). 

See index.h Header file for more information. */

//includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../common/pagedir.h"

//the index structure
typedef struct index {
    hashtable_t* wordIndex;
}  index_t;


/********Local Functions**********/
void index_printLine(void* arg, const int key, const int count);
void iterate_helper(void*arg, const char* key, void* item);

/***********index_new************/
//make a new index with the given number of slots
index_t* index_new(const int num_slots){  
    if (num_slots <= 0){
        return NULL;
    }
    else{
        //make a new index 
        index_t* newIndex = mem_malloc(sizeof(index_t));
        if (newIndex == NULL){
            return NULL;
        }
        //initialize index as a new *empty* hashtable
        newIndex -> wordIndex = hashtable_new(num_slots);
        return newIndex;
        
    }
}

/***********index_save************/
//saves the input word into the index at the docId, making a new counter if not there or incrementing if already there
void index_save(index_t* index, const char* word, const int docID){
    //search the index's hashtable for the given word
    counters_t* wordCounter = hashtable_find(index -> wordIndex, word);
    //if hashtable_find returns an item for that word (which would be its counter)
    if (wordCounter != NULL){
        //increment the counter for the given word at its docID
        counters_add(wordCounter, docID); 
    }
    else{ 
        //make a new counter to insert
        counters_t* newCounter = counters_new();
        //insert that counter into the table
        hashtable_insert(index -> wordIndex, word, newCounter);
        //increment that docid in the counter
        counters_add(newCounter, docID);
    }
    return;
}

/***********index_save************/
//prints out the index to the given file in the indexPage format:
//that is, each line contains a word followed by alternating docIDs with the 
//number of times that the word occurs in that doc.
void index_print(index_t* index, FILE* fp){
    hashtable_t* hashtable = index -> wordIndex;
    hashtable_iterate(hashtable, fp, iterate_helper);
}

/***********index_delete************/
//deletes the entire index from memory.
void index_delete(index_t* index){
    hashtable_t* hashtable = index -> wordIndex;
    hashtable_delete(hashtable, (void (*)(void*))counters_delete);
    mem_free(index);
    return;
}

/*iterate_helper- helper function for the index_print function*/
//receives arg (fp), key (word), and item (counters), prints the word, calls counters iterate
void iterate_helper(void*arg, const char* key, void* item){
   fprintf(arg, "%s ", key); //prints the word to the file
   counters_iterate(item, arg, index_printLine); //calls index_printLine on each counter
   fprintf(arg, "\n");
}


/*index_printLine- second helper function for the index_print function within the iterate_helper function */
//receives arg (fp), key (docID), and item (wordcount)
void index_printLine(void* arg, const int key, const int count){
   fprintf(arg, "%d %d ", key, count); // prints the docID followed by the word'scount with a space in between
}