# CS50 TSE Indexer
## Implementation Spec

This implementation spec will focus on the indexer's:

-  Data structures
-  Control flow: pseudo code for overall flow, and for each of the functions
-  Detailed function prototypes and their parameters
-  Error handling and recovery
-  Testing plan

## Data structures 
The main data structures relied upon for the indexer are `hashtable` and `counters`. I use these two structures to create a new `index` structure, which is ultimately a wrapper for a hashtable with some added capabilities. 

The `index` structure contains one hashtable, which is configured to hold `char* word` keys associated with `counters_t*` items. Each counter within the word holds an `int` key representing the document ID a certain word was found in associated with another `int` item that represents the number of times the word occurred in that document. 

The indexer itself then creates an empty index structure into which it later adds words as they are found and increments the counter for at the docID they were found in. 
## Control flow

The Indexer is implemented in one file `indexer.c`, with two functions.

### main

The `main` method validates and parses the arguments (verifying the filepaths and opening the file to which the index will be written). It then creates an index with `indexBuild`, which loops through documents and calls `indexPage`, then returning the completed index. Then it calls the `index_print` method upon the new index, which outputs the contents of the index in the specified format to the outfile.

### indexBuild

Given a pageDirectory address as a `char*`, fetch a webpage from every pageDir file, adding all of the words found in that page to the index and finally returning it. 
* The index is initialized with 500 spaces (a rough estimate for the number of words we will be holding)

Pseudocode: 

    initialize a new index with 500 spaces
    loop through each pageDir document
        load a webpage (pagedir_load) from that pagedir
        if the page was loded correctly
            call index page on that page
        else
            print error and exit 1
        delete the current webpage structure
        close the file
        increment the docID to open the next file and open it
    free the pageDirName string
    return the final index. 

### indexPage

Takes an index structure, a webpage, and a docID: this is the webpage fetched from the given doc. Add every word to that page into the index. 

Pseudocode:

    while there are more words in the webpage
        if the word is at least three characters
            normalize that word
            save the normalized word into the given index with its docID
            free the normalized word
        free the word
    return
## Other modules

### index

We create the `index_t` structure mentioned above to hold our word hashtable. This is also stored within the indexer directory, and is used by the indexer to build, maintain, and print the index. 

The index module implementes four main methods: `index_new`, `index_save`, `index_print`, and `index_delete`. 

Pseudocode for `index_new`:

    validate number of slots
    malloc for the index struct
    verify it was created correctly
    initialize the hashtable stored in the index's `wordIndex`
    return the the new index

Pseudocode for `index_save`:

    search the index's hashtable for the given word
    if the hashtable already holds a counter for that word:
        add the word to the counters with its docID
    if not, 
        make a new counter
        insert that counter into the hashtable under the current word
        add the word to the counters with its docID

Pseudocode for `index_delete`:

    delete the hashtable passing the counters_delete function as the item function to delete all of the counter items stored with their word keys.
    free the index 

Pseudocode for `index_print`:

    iterate through the hashtable
        print the word to the file
        iterate through the counters
        print each counter out in the correct format to the file

### pagedir

The pagedir module previously used in the `crawler` was built upon for the indexer, adding two new methods: `pagedir_validate` and `pagedir_load`. 

Pseudocode for `pagedir_validate`: 

    attempt to open a .crawler file in the pageDirectory
    if the file opened unsuccessfully:
        free the name string and return false
    if the file opened successfully: 
        close the file
        free the name string
        return true

Pseudocode for `pagedir_load`: 
    
    If the input file doesn't exist: 
        error and exit non-zero
    Read the URL from the first line of the file
    Read the depth from the next line and convert it to an int
    create a new webpage structure
    fetch that webpage's HTML
    if success, return the new page, otherwise, return NULL 

### word

The word module contains just one method to normalize the given word. 

Pseudocode for `word_normalize`: 

    determine the word's length and allocate mem for the new string
    iterate through each character of the word
        change that character to lowercase and set that space in the new string to the lowercase character
    null terminate the string
    return it

### libcs50

We leverage the modules of libcs50, most notably `counters`, `hashtable`, and `webpage`.
See that directory for module interfaces.
The new `webpage` module allows us to represent pages as `webpage_t` objects, to fetch a page from the Internet, and to scan a (fetched) page for URLs. 

## Function prototypes

### indexer

Detailed descriptions of the functions below are given both above and in the indexer.h header file

```c
int main(const int argc, char* argv[]);
index_t* indexBuild(const char* pageDirectory);
void indexPage(index_t* index, webpage_t* webpage, int docID);
```

### pagedir

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's declaration in `pagedir.h` and is not repeated here.

```c
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
webpage_t* pagedir_load(FILE* fp);
bool pagedir_validate(const char* pageDirectory);
```
### word

The word module is very simple, including just one function `word_normalize` that takes a word and converts it to all lowercase letters for storage. See word.h for a detailed description. 

```c
char* word_normalize(char* word);
```
## Error handling and recovery

All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Within the new modules implemented, structures and files are checked to ensure that new memory was successfully allocated before usage to prevent errors. 

## Testing plan

Here is an implementation-specific testing plan.

### Unit testing

The main units used for the indexer are `indexer`, `pagedir`, `word`, and `index`. 

The indexer represents the whole system and is covered below. 

The pagedir and word modules are utilized by the indexer, and were tested rigorously throughout the design of the indexer. 

The index module is more complicated, and was accordingly tested both through the use of the indexer and its own testing module, `indextest.c`. 

### Integration/system testing

We write a script `testing.sh` that invokes the indexer several times, with a variety of command-line arguments.
First, a sequence of invocations with erroneous arguments, testing each of the possible mistakes that can be made.
Second, a run with valgrind over a moderate-sized test case (such as `toscrape` at depth 1).
Third, runs over all three CS50 websites (`letters` at depths 0,1,2,10, `toscrape` at depths 0,1,2,3, `wikipedia` at depths 0,1,2).
Run that script with `bash -v testing.sh` so the output of crawler is intermixed with the commands used to invoke the crawler.
Verify correct behavior by studying the output, and by sampling the files created in the respective pageDirectories.

> For Lab 4, as noted in the assignment, you may submit a smaller test run.
> Furthermore, we recommend turning off detailed logging output for these tests, as they make `testing.out` rather large!
