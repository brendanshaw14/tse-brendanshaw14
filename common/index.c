/* Index Module for the Indexer component of the TSE lab 

Author: Brendan Shaw

CS50- Winter 2023
*/
//includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../common/pagedir.h"


typedef struct index {
    hashtable_t* wordIndex;
}  index_t;


/********Local Functions**********/
void index_printLine(void* arg, const int key, const int count);
void iterate_helper(void*arg, const char* key, void* item);



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
/*
if the word is already in the index:
    add the docID to the counter or increment it if it already exists
else (the word isn't in the index)
    add the word to the index's hashtable
    make a new counters for that word
        counters add the docID (should make a counter in the counterset with that docid and a count of 1)

*/
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

//print out the index
/*
iterate through the hashtable, 
*/
void index_print(index_t* index, FILE* fp){
    hashtable_t* hashtable = index -> wordIndex;
    hashtable_iterate(hashtable, fp, iterate_helper);
}


//delete the index
void index_delete(index_t* index){
    hashtable_t* hashtable = index -> wordIndex;
    hashtable_delete(hashtable, (void (*)(void*))counters_delete);
    mem_free(index);
    return;
}

//receives arg (fp), key (word), and item (counters), prints the word, calls counters iterate
void iterate_helper(void*arg, const char* key, void* item){
   fprintf(arg, "%s ", key); //prints the word to the file
   counters_iterate(item, arg, index_printLine); //calls index_printLine on each counter
   fprintf(arg, "\n");
}

//receives arg (fp), key (docID), and item (wordcount)
void index_printLine(void* arg, const int key, const int count){
   fprintf(arg, "%d %d ", key, count); // prints the docID followed by the word'scount with a space in between
}