/* Index.H : Header file for the index.c module

Author: Brendan Shaw

CS50- winter 2023 

*/

#include <stdlib.h>
#include <stdio.h>



typedef struct index index_t;

/***********index_new***************/
/*Creates a new index with the given number of slots*/
index_t* index_new(const int num_slots);

/***********index_new***************/
/*Creates a new index with the given number of slots*/
void index_save(index_t* index, const char* word, const int docID);

/***********index_new***************/
/*Creates a new index with the given number of slots*/
void index_delete(index_t* index);

/***********index_new***************/
/*Creates a new index with the given number of slots*/
void index_print(index_t* index, FILE* fp);