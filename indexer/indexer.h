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

/*********indexBuild*********/
/*Given a pageDirectory address as a `char*`, 
    fetch a webpage from every pageDir file,
    adding all of the words found in that page 
    to the index and finally returning it. 
* The index is initialized with 500 spaces 
(a rough estimate for the number of words we will be holding) 

Returns the final index, also relies on helper function indexPage below.*/
index_t* indexBuild(const char* pageDirectory);

/*********indexPage*********/
/* given an index, a webpage, and a docID as arguments,
indexPage iterates through the words on the webpage and stores 
them in the index accordingly. */
void indexPage(index_t* index, webpage_t* webpage, int docID);