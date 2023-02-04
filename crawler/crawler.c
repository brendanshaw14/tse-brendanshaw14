/* Crawler.c- web crawler for the cs50 TSE lab 
*
* Author: Brendan Shaw- February 2023
* CS50- 23W
* 
* Inputs: stdin- runs through the command line
* Outputs: outputs to stdout, as well as file output with site data to pageDir location (in these tests, ../data/letters)
* 
* Usage (pulled from 'requirements' git page):
Execute from a command line with usage syntax ./crawler seedURL pageDirectory maxDepth
  where seedURL is an 'internal' directory, to be used as the initial URL,
  where pageDirectory is the (existing) directory in which to write downloaded webpages, and
  where maxDepth is an integer in range [0..10] indicating the maximum crawl depth. 

*Compile: `make` using makefile. `make test` for test and `make valgrind` for valgrind test. See makefile for tdetails.

  ****SEE HEADER FILE FOR MORE DETAILS ABOUT FUNCTIONS.**** 
*/

//includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"

//function headers
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
static void logr(const char *word, const int depth, const char *url);
//takes 3 args- seedURL pageDirectory and maxDepth

//main
int main(const int argc, char* argv[]){
  //declare variables to store inputs
  char* seedURL = NULL;
  char* pageDirectory = NULL;
  int maxDepth;
  //parse arguments, then crawl!
  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
  crawl(seedURL, pageDirectory, maxDepth);
  return 0;
}

//validates command input, then initializing the given pagedirectory and saving inputs for later use
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth){
  //check for valid number of arguments
  if(argc != 4){
    printf("Error: Invalid Number of arguments.");
    exit(1);
  }
  //normalize the URL and validate it is an internal URL, storing it in seedURL, and exiting if error
  *seedURL = normalizeURL(argv[1]);
  if (isInternalURL(*seedURL)==false){
    printf("Error: Invalid or External URL");
    exit(1);
  }
  //call pagedir_init on the input pageDirectory, exiting if failure. 
  *pageDirectory = argv[2];
  if(pagedir_init(*pageDirectory) != true){
    printf("Error: Unable to create page directory");
    exit(1);
  }
  //verify that max depth isn't out of range
  sscanf(argv[3], "%d", maxDepth);
  if (*maxDepth < 0 || *maxDepth > 10){
    printf("Error: Invalid max depth: choose a number between 1 and 10.");
    exit(1);
  }
  return; 
}

//master crawl function: initializes pagesSeen hashtable and pageBag bag, inserts the seed page,
//and pulls pages from the bag to send to pagescan, which adds new valid pages to scan, until the bag is empty. 
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth){
  //initialize hashtable and insert seedURL
  hashtable_t* pagesSeen = hashtable_new(200);
  hashtable_insert(pagesSeen, seedURL, "");
  //initialize the bag and insert the seed page
  bag_t* pageBag = bag_new();
  webpage_t* seedPage = webpage_new(seedURL, 0, NULL);
  bag_insert(pageBag, seedPage);
  //extract the seed page from the bag and store in current page to start looping through
  webpage_t* currentPage = bag_extract(pageBag); 
  int docID = 1; 
  //loop thorugh pages in the bag
  while (currentPage != NULL){
    //fetch page and exit upon error
    if(webpage_fetch(currentPage)==false){
      printf("Error: Webpage Fetch Failed.");
      exit(0);
    }
    //if success, save the page, increment the docID for storage, and call pageScan if not at max depth
    else{
      logr("Fetched", webpage_getDepth(currentPage), webpage_getURL(currentPage));
      pagedir_save(currentPage, pageDirectory, docID);
      docID ++;
      if (webpage_getDepth(currentPage) < maxDepth){
        logr("Scanning", webpage_getDepth(currentPage), webpage_getURL(currentPage));
        pageScan(currentPage, pageBag, pagesSeen);

      }
      //delete the current page
      webpage_delete(currentPage);
    }
    //loop to the next page
    currentPage = bag_extract(pageBag); 
  }
  //cleanup: delete hashtable and bag
  hashtable_delete(pagesSeen, NULL);
  bag_delete(pageBag, webpage_delete);
  return;
}

//scans the given page, adding new internal pages within maxDepth to to the bag to crawl and the pagesSeen hashtable
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
  int pos = 0;
  //const int newDepth = webpage_getDepth(page);
  char* nextURL;
  while ((nextURL = webpage_getNextURL(page, &pos))!= NULL){
    logr("Found", webpage_getDepth(page), nextURL);
    if (isInternalURL(nextURL) == false){
      logr("IgnExtrn", webpage_getDepth(page), nextURL);
      free(nextURL);
    }
    else{
      if (hashtable_insert(pagesSeen, nextURL, "") == true){
        webpage_t* newPage = webpage_new(nextURL, webpage_getDepth(page) + 1, NULL);
        bag_insert(pagesToCrawl, newPage);
        logr("Added", webpage_getDepth(newPage)-1, nextURL);
      }
      else{
        logr("IgnDupl", webpage_getDepth(page), nextURL);
        free(nextURL);
      }
    }
  }
  return; 
}

//log function given from knowledge unit- used in testing                                  
static void logr(const char *word, const int depth, const char *url)
{
  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
}