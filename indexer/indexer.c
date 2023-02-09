/* INDEXER

Author: Brendan Shaw 

CS50- Winter 2023

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
webpage_t* pageFromFile(FILE* fp);

//parse the command line, validate parameters, initialize other modules
//call indexBuild, with pageDirectory

//parse arguents and call other modules
//indexer pageDirectory indexFilename
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
    index_t* index = indexBuild(argv[1]);
    index_print(index, stdout);
    fclose(fp);
    index_delete(index);
  return 0;
}

//builds an in-memory index from webpage files it finds in the pageDirectory;
//creates a new 'index' object
  //loops over document ID numbers, counting from 1
    //loads a webpage from the document file 'pageDirectory/id'
    //if successful, 
      //passes the webpage and docID to indexPage
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
  while (fp != NULL){
    currentPage = pageFromFile(fp);
    if (currentPage != NULL){
      indexPage(pageIndex, currentPage, docID);
    }
    webpage_delete(currentPage);
    fclose(fp);
    docID++; 
    sprintf(pageDirName, "%s/%d", pageDirectory, docID);
    fp = fopen(pageDirName, "r");
  }
  //free pagedir nme and index
  mem_free(pageDirName);
  return pageIndex;
}

//which scans a webpage document to add its words to the index.//
 //steps through each word of the webpage,
   //skips trivial words (less than length 3),
   //normalizes the word (converts to lower case),
   //looks up the word in the index,
     //adding the word to the index if needed
   //increments the count of occurrences of this word in this docID
void indexPage(index_t* index, webpage_t* webpage, int docID){
  //loop through words
  int position = 0;
  char* word; //FREE THIS LATER
  while ((word = webpage_getNextWord(webpage, &position)) != NULL){
   if (strlen(word) >= 3){
    char* normalizedWord = word_normalize(word); //FREE THIS LATER
    printf("Saving %s with docID %d\n", normalizedWord, docID);
    index_save(index, normalizedWord, docID);
    mem_free(normalizedWord);
   }
   mem_free(word);
  }
    return;
}

//returns a webpage from a page file 
webpage_t* pageFromFile(FILE* fp){
  //test NULL
  if (fp == NULL){
    printf("Error: Unable to read page file");
    exit(1);
  }
  //get URL
  char* URL = file_readLine(fp);
  //get the string and make a pointer to store the int in 
  char* depthString = file_readLine(fp);
  int depth;
  sscanf(depthString, "%d", &depth);
  //make page
  webpage_t* newPage = webpage_new(URL, depth, NULL);
  if (webpage_fetch(newPage) == true){
    mem_free(depthString);
    return newPage;
  }
  else{
    return NULL;
  }
} 

