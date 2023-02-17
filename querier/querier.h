/* Querier.h- header file for the final part of the CS50 TSE Lab. 

Author: Brendan Shaw, February 2023
CS50- Winter 2023

See querier.h for detailed descriptions of methods and functions. 

Usage: ./querier <pageDirectory> <indexFile> 

To use, make test. 
*/

//includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"

//headers
index_t* indexFromFile(FILE* indexFile);
void getQueries(index_t* pageIndex, char* pageDir);
char** tokenizeQuery(char* input, int* numWords, char* output);
bool verifyQuery(char** tokenizedQuery);
void normalizeQuery(char** input, int numWords);
void handleQuery(char** input, int numWords, index_t* pageIndex, char* pageDir);
void countersMerge(counters_t* result, counters_t* temp);
void mergeHelper(void* result, const int key, const int tempCount);
void countersIntersect(counters_t* temp, counters_t* new);
void intersectHelper(void* args, const int newKey, const int newCount);
void printQueryResult(counters_t* result, char* pageDir);
void getNumDocs(void* counter, const int docID, const int score);
void getHighestScore(void* argstruct, const int docID, const int score);
int fileno(FILE *stream);

