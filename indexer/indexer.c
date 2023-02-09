/* INDEXER- a c program to read web crawler file output and create an inverted index

Author: Brendan Shaw, CS50- Winter 2023

Inputs: file input from a specified .crawler directory with crawler outputs
Output: file output to specified indexPageDir to save

Compile: use `make` to compile indexer and common library, `make test` to test on the "letters" crawler output file in the "data" directory, 
  and `make valgrind` for the same test command with valgrind output`

Usage: ./indexer <pageDirectory> <indexFileDirectory>

See implementation spec for more information*/

//includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"

//function headers
index_t* indexBuild(const char* pageDirectory);
void indexPage(index_t* index, webpage_t* webpage, int docID);

//parse the command line, validate parameters, initialize other modules
//call indexBuild, with pageDirectory
int main(const int argc, char* argv[]){
    //validate two args
    if (argc != 3){
        printf("Error: Invalid number of args.");
        exit(1);
    }
    //test if .crawler exists
    if(pagedir_validate(argv[1]) != true){
        printf("Error: specified pageDir doesn't have .crawler file");
        exit(1);
    }
    //create index file 
    FILE* fp = NULL;
    fp = fopen(argv[2], "w");
    if (fp == NULL){
      printf("Error: Failed to create/open indexFile");
      exit(1);
    }
    //build the index!
    index_t* index = indexBuild(argv[1]); 
    index_print(index, fp); // print the index to the file
    fclose(fp);
    index_delete(index); // delete it
  return 0;
}

//builds an in-memory index from webpage files it finds in the pageDirectory;
index_t* indexBuild(const char* pageDirectory){
  //make new index with 500 spots to hold words
  index_t* pageIndex = index_new(500);
  //splice id to find file id to open
  int docID = 1;
  char* pageDirName = mem_malloc(strlen(pageDirectory) + 10);
  sprintf(pageDirName, "%s/%d", pageDirectory, docID);
  //open the file and send to pageFromFile
  webpage_t* currentPage;
  FILE* fp = fopen(pageDirName, "r");
  //loop through the pages
  while (fp != NULL){
    currentPage = pagedir_load(fp);
    if (currentPage != NULL){ //ensure page was created corretly
      indexPage(pageIndex, currentPage, docID);
    }
    else { //exit if failure
      printf("Failed to create webpage from file");
      exit(1);
    }
    webpage_delete(currentPage); //delete current 
    fclose(fp);
    docID++; //go to the next file
    sprintf(pageDirName, "%s/%d", pageDirectory, docID); //make its name
    fp = fopen(pageDirName, "r"); //open it with that name
  }
  //free pagedir name and return the final index 
  mem_free(pageDirName);
  return pageIndex;
}

//scans a webpage document to add its words to the index
void indexPage(index_t* index, webpage_t* webpage, int docID){
  //loop through words
  int position = 0;
  char* word; 
  while ((word = webpage_getNextWord(webpage, &position)) != NULL){
   if (strlen(word) >= 3){ //make sure it's longer than 2
    char* normalizedWord = word_normalize(word); //normalize 
    index_save(index, normalizedWord, docID); //add to index
    mem_free(normalizedWord); 
   }
   mem_free(word);
  }
    return;
}

