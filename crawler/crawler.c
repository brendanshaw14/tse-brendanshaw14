/* Crawler.c- web crawler for the cs50 TSE lab written by Brendan Shaw
*
*
*
*parse the command line, validate parameters, initialize other modules
add seedURL to the bag of webpages to crawl, marked with depth=0
add seedURL to the hashtable of URLs seen so far
while there are more webpages in the bag:
    extract a webpage (URL,depth) item from the bag
    pause for one second
    use pagefetcher to retrieve a webpage for that URL
    use pagesaver to write the webpage to the pageDirectory with a unique document ID
    if the webpage depth is < maxDepth, explore the webpage to find the links it contains:
      use pagescanner to parse the webpage to extract all its embedded URLs
      for each extracted URL:
        normalize the URL (per requirements spec)
        if that URL is internal (per requirements spec):
          try to insert that URL into the *hashtable* of URLs seen;
            if it was already in the table, do nothing;
            if it was added to the table:
               create a new webpage for that URL, marked with depth+1
               add that new webpage to the bag of webpages to be crawled
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"

static void logr(const char *word, const int depth, const char *url);
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
void deleteWeb(void*item);
//takes 3 args- seedURL pageDirectory and maxDepth

int main(const int argc, char* argv[]){
  char* seedURL = NULL;
  char* pageDirectory = NULL;
  int maxDepth;

parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
crawl(seedURL, pageDirectory, maxDepth);

return 0;
}
//parses arguments

static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth){
  if(argc != 4){
    printf("Error: Invalid Number of arguments.");
    exit(1);
  }

  //normalize the URL and validate it is an internal URL
  *seedURL = normalizeURL(argv[1]);
  if (isInternalURL(*seedURL)==false){
    printf("Error: Invalid or External URL");
    exit(1);
  }
  //call paagedir_init
  *pageDirectory = argv[2];
  if(pagedir_init(*pageDirectory) != true){
    exit(1);
  }
  //validate depth
  sscanf(argv[3], "%d", maxDepth);
  if (*maxDepth < 1 || *maxDepth > 10){
    printf("Error: Invalid max depth: choose a number between 1 and 10.");
    exit(1);
  }
  return; 
}

//loops over pages to explore, until the list is exhausted/
/*initialize the hashtable and add the seedURL
initialize the bag and add a webpage representing the seedURL at depth 0
while bag is not empty
	pull a webpage from the bag
	fetch the HTML for that webpage
	if fetch was successful,
		save the webpage to pageDirectory
		if the webpage is not at maxDepth,
			pageScan that HTML
	delete that webpage
delete the hashtable
delete the bag*/
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth){
  hashtable_t* pagesSeen = hashtable_new(200);
  hashtable_insert(pagesSeen, seedURL, "");
  bag_t* pageBag = bag_new();
  webpage_t* seedPage = webpage_new(seedURL, 0, NULL);
  bag_insert(pageBag, seedPage);

  webpage_t* currentPage = bag_extract(pageBag); 
  int docID = 1; 
  while (currentPage != NULL){
    if(webpage_fetch(currentPage)==false){
      printf("Error: Webpage Fetch Failed.");
      exit(0);
    }
    else{
      pagedir_save(currentPage, pageDirectory, docID);
      docID ++;
      //printf("Current Depth:%d : Max Depth: %d", webpage_getDepth(currentPage), maxDepth);
      if (webpage_getDepth(currentPage) < maxDepth){
        pageScan(currentPage, pageBag, pagesSeen);
      }
      webpage_delete(currentPage);
    }
    currentPage = bag_extract(pageBag); 
  }
  hashtable_delete(pagesSeen, NULL);
  bag_delete(pageBag, webpage_delete);

  return;

}

//fetches a page from a URL
//pageFetcher


//extracts URLs from a page and processes each one
/*while there is another URL in the page
	if that URL is Internal,
		insert the webpage into the hashtable
		if that succeeded,
			create a webpage_t for it
			insert the webpage into the bag
	free the URL*/

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
  int pos = 0;
  //const int newDepth = webpage_getDepth(page);
  char* nextURL;
  while ((nextURL = webpage_getNextURL(page, &pos))!= NULL){
    const char* constURL = nextURL;
    if (isInternalURL(constURL) == false){
      logr("IgnExt", webpage_getDepth(page), nextURL);
      free(nextURL);
    }
    else{
      if (hashtable_insert(pagesSeen, constURL, "") == true){
        webpage_t* newPage = webpage_new(nextURL, webpage_getDepth(page) + 1, NULL);
        bag_insert(pagesToCrawl, newPage);
        logr("Added", webpage_getDepth(newPage), nextURL);
      }
      else{
        logr("IgnDupl", webpage_getDepth(page), nextURL);
        free(nextURL);
      }
    }
  }
  return; 
}

//outputs a page to the the appropriate file
//pageSaver

void deleteWeb(void*item){
  return;
}

// log one word (1-9 chars) about a given url                                   
static void logr(const char *word, const int depth, const char *url)
{
  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
}