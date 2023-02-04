#CS50 LAB 4
##CS50 23W

### Crawler

A `crawler` is in summary a program that starts from a seed URL, scans that page for any other URLs, and then scanning all of those pages for URLs until it reaches the max depth provided by the user. This can take some time, so the max depth is limited by default to 10.

### Usage

The `crawler` program includes a `crawler.h` header file and a `Makefile` for usage. After compiling, the crawler takes three arguments: a `seedURL`, a `pageDirectory`, and a `maxDepth` _(see header file for more info)_. 
Run with `./crawler <seedURL> <pageDirectory> <maxDepth>`.

```c
int main(const int argc, char* argv[])
static void parseargs(const int argc, char* argv[], char** seedurl, char** pagedirectory, int* maxdepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
```

### Implementation 

The crawler uses a bag (functionally a stack) of webpages to queue new pages for search, and a hashtable of URLS to check if the page in question has already been visited. The `main` method handles calling other functions within crawler. 

### Assumptions
No major assumptions were made. The crawler functions just like the implementation spec, and has no known errors. 

### Files
* `Makefile` - compilation procedure and testing
* `crawler.h` - the header file 
* `crawler.c` - the program
* `testing.h` - the testfile
* `testing.out` - the result of `bash -v testing.sh &> testing.out`

### Compilation

To compile, `make`. 

### Testing 

`bash -v testing.sh &> testing.out` runs test file, which carries out a variety of tests showing both edge cases and valid inputs. The tests demonstrates correct funciton of crawler for multiple sites.
See `testing.out` for test output. 
For valgrind, `myvalgrind ./crawler`. 
