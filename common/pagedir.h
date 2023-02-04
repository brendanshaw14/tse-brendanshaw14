/* Pagedir.c- header file for the pagedir module for the cs50 crawler TSE lab component 
*
* Author: Brendan Shaw- February 2023
* CS50- 23W
* 
* Included in crawler.c for use by the crawler 
*
*Compile: `make` using makefile. Alternatively, ``make` in the crawler directory itself to run the common folder's makefile
*/

//includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include <string.h>

/**************** pagedir_init ****************/
/* Create a new (empty) .crawler file in the pageDirectory to mark where crawler has been.
 *
 * Caller provides:
 *  valid pageDirectory to input  
 * We do:
 *   Create a .crawler file in the directory and ensure it is opened correctly
 */
bool pagedir_init(const char* pageDirectory);

/**************** pagedir_save ****************/
/* Create a new file in the pageDirectory to write the contents of the given page to
 *
 * Caller provides:
 *  valid pageDirectory to write the file to, valid webpage to write contents of into pageDirectory, and docID 
 * We do:
 *   Create a file with an integer title (docID) in the directory and ensure it is opened correctly
 *   Print the contents of the webpage to the file 
 *      -depth
 *      -URL
 *      -HTML contents
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);






