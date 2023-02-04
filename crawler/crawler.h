
/* Crawler.h- header for web crawler for the cs50 TSE lab 
*
* In summary, the crawler is given a seedURL, max depth and output directory. The crawler starts at the seedURL, 
* reading that page, then checking for any other pages found within that page. It accesses those pages (of depth 1) 
* for more pages (which would have a depth one higher than the previous), reading them and outputting into the given directory. 
*
* Author: Brendan Shaw- February 2023
* CS50- 23W
* 
*
* Usage (pulled from 'requirements' git page):
Execute from a command line with usage syntax ./crawler seedURL pageDirectory maxDepth
  where seedURL is an 'internal' directory, to be used as the initial URL,
  where pageDirectory is the (existing) directory in which to write downloaded webpages, and
  where maxDepth is an integer in range [0..10] indicating the maximum crawl depth. 

*Compile: `make` using makefile. `make test` for test and `make valgrind` for valgrind test. See makefile for tdetails.

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include <string.h>


/**************** functions ****************/


/**************** main ****************/
/* Declare pointer variables, call parseArgs and crawl */
int main(const int argc, char* argv[]);

/**************** parseArgs ****************/
/* Parse command line arguments 
 *
 * Caller provides:
 *  Input seedURL, pageDirectory, and maxDepth
 * We do:
 *  Initialize variables and the pageDirectory, but exit program if arguments are invalid for some reason
 * We guarantee:
 *  If valid arguments are provided, they will be stored to the given pointers correctly
 */
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);

/**************** crawl ****************/
/* Traverse all the seedURL's included webpages and their descendants until a depth of 10
 *
 * Caller provides:
 *  valid seedURL, pageDirectory, and maxDepth 
 * We do:
 *  validate, search, and save (into provided pageDirectory) all webpages and their descendants from the seed page until max depth is reached
 * We guarantee:
 *  No duplicates are created, no external pages (outside of organization) are visited. 
 */
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);

/**************** pageScan ****************/
/* Scan the given page for new URL, validating them and adding them to the pagesToCrawl bag and adding seen pages to the pagesSeen hashtable
 *
 * Caller provides:
 *  valid pointer to a page as well as the correct pagesToCrawl bag and pagesSeen hashtable 
 * We do:
 *    Scan this page for included valid pages, update bag and hashtable 
 * We guarantee:
 *  invalid pages and duplicates are ignored
 */
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);



