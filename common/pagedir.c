/*Pagedir.c- C module implementing multiple functions to inidiate a pagedir,save a webpage to a pagedir file, 
    validate that a pagedir was visited by the crawler, and load a webpage from a given file
Author: Brendan Shaw- CS50 Winter 2023

See pagedir.h file for more info. 
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../libcs50/file.h"

//function headers
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(const char* pageDirectory);
webpage_t* pagedir_load();

//initialize the page directory
bool pagedir_init(const char* pageDirectory){
    char* newDir = mem_malloc(strlen(pageDirectory)+10);
    sprintf(newDir, "%s/.crawler", pageDirectory);
    //create file
    FILE* fp = fopen(newDir, "w");
    if (fp == NULL){
        printf("Error: pagedir_init unable to create file");
        mem_free(newDir);
        return false;
    }
    mem_free(newDir);
    fclose(fp);
    return true; 
}

//save the given webpage to the given pagedirectory
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
    int docIDString_len = log10(docID) + 1; 
    char* newDir = malloc(strlen(pageDirectory) + docIDString_len + 2);
    sprintf(newDir, "%s/%d", pageDirectory, docID);

    FILE* fp = fopen(newDir, "w");
    //print webpage to file
    fprintf(fp, "%s\n%d\n%s\n", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
    mem_free(newDir);
    fclose(fp);
    return;
}

//validate that the given page directory was visited by crawler
bool pagedir_validate(const char* pageDirectory){
    FILE* fp = NULL;
    char* crawlerFileDir = mem_malloc(strlen(pageDirectory)+ 10);
    sprintf(crawlerFileDir, "%s/.crawler", pageDirectory);
    fp = fopen(crawlerFileDir, "r");
    if (fp == NULL){
        mem_free(crawlerFileDir);
        return false;
    }
    else{
        fclose(fp);
        mem_free(crawlerFileDir);
        return true;
    }
}

//load a page from a file in the pageDir 
webpage_t* pagedir_load(FILE* fp){
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