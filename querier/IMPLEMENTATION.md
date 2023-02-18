# CS50 TSE Indexer
## Implementation Spec

This implementation spec will focus on the querier's:

-  Data structures
-  Control flow: pseudo code for overall flow, and for each of the functions
-  Detailed function prototypes and their parameters
-  Error handling and recovery
-  Testing plan

## Data structures 
The main data structures relied upon for the querier are `index` and `counters`.

The querier also uses two very small helper structures, `maxdoc` and `counterArgs` to be passed as arguments to iterators when needed. `counterArgs` holds just two counters (the ones being merged or intersected), while `maxdoc` holds just two ints: a docID and a score. 

The querier does create its own index loaded from the index file to pull words from. 

## Control flow

The querier is implemented in one file `querier.c` with the following functions: 

### main

The `main` method validates and parses the arguments (verifying the filepaths and opening the indexfile. It then creates the index by calling `indexFromFile`, calls `getQueries`, and frees the index and file after each function runs. 

### indexFromFile

Given an indexfile, create an index holding exactly the words in the indexFile to represent its contents. 

Pseudocode: 

    initialize a new index
    loop through each word in the file
        scan pairs of the numbers following that word
            for each pair
                save that word in the index
        free the word
    free storage variables

### getQueries

Reads one line at a time into standard in, calling `tokenizeQuery`, `normalizeQuery`, and `handleQuery` on each line. 

Pseudocode:

    print the first search prompt
        if the line has contents
            tokenize it
            if that worked, tokenize it
            pass it to handlequery
            free the storage variables
            reset the number of woreds
        if the line doesn't have contents
            free the storage variables
        free the input line and print the prompt again
    free the line and numwords storage int

### tokenizeQuery

Reads through each character in the query line and handles it accordingly to build a string array. 

Pseudocode: 
    
    make a string array to store pointers to the first character of each word in a new line string that we save
    for each character
        if the character is a letter 
            if we aren't already reading a word
                remember we are reading a word
                increment the char index
                save that character into a new line string with just characters
                save a pointer to that char at the word index
            else
                save the character into the new line string
                increment the char index
        if the character is a space
            if we are within a word
                save the null terminator to the new line string
                increment the number of words
                increment the character index
                remember we are no longer within a word
        otherwise
            print invalid character error
            return the NULL line
        check that there are less than 200 words still (for mem)
    if the loop terminates while wtill within a word
        add the null terminator the the new line string
    return the output string array

### normalizeQuery

Takes an input string array and the number of words in it and normalizes all of those words

Pseudocode: 
    
    for each word in the arrar
        normalize it and save that word in mem
        copy the normalized word into the location where the current word is
        free that string

### handleQuery

Takes the ordered array of words in the query and handles them. (see requirements spec for how this is approached)

Pseudocode: 

    If the first or last word is and or or
        print error and return
    initialize a result counter
    declare a temp counter 
    while there are still more words
        if that word is and
            print error if the next word is and or or
        otherwise, increment the word index
        if the word is or
            print error if the next word is and or or
            remember that we are no longer intersecting the new words
            merge temp into the result
            inrcrement the index
        else (the word isn't and or or)
            if we aren't currently intersecting
            remember that we are now intersecting
            if we are already intersecting
                get that word's counters from the index
                intersect temp and that counters
                switch the temp and result (because they are inversed in the intersect method)
                increment the index
    merge result and temp
    print the query result
    delete the result
    return

### printQueryResult 

takes the counter of docIDs and their scores resulting from the search and prints it in order

Pseudocode: 

    iterate through the counters to see how many there are
    if there are no matches, print no matches
    otherwise
    print how many matches there are
    loop through the matches
        find the highest scoring one
        print its id score and url
        set its score to 0 after printing
        reset the highest score

### countersMerge

merges two input counters

pseudocode: 

    iterate through the temp counters, passing result as an arg and mergeHelper as the function

mergeHelper: 

    if the counter doesn't yet exist in the result
        add it to the result
    if it does exist
        sum the scores and set the result to have the sum

### countersIntersect

intersects two input counters

pseudocode: 
    
    create a new counterArgs struct to hold temp and new
    iterate through the new counters and pass the counterArgs as an arg and intersect helper as a function

intersectHelper: 

    if the counter exists in the result
        find which counter has a smaller value
        set the new counter to the result value 
    if it doesn't exist
        set the counters score to 0 so it won't be printed

### getNumDocs

helper function for the counters iterator to keep track of how many documents there are

Pseudocode: 
    
    if the counters score isn't zero
        increment the variable storing the number of results
    otherwise do nothing

### getHighestScore

helper function for the counters iterator to retrieve the highest scoring doc's ID and score

Pseudocode: 
    
    if the counters score is higher than the current highest score
        save it and its ID
    otherwise do nothing

## Other modules 

### libcs50

We leverage the modules of libcs50, most notably `counters`, `hashtable`, and `webpage`.
See that directory for module interfaces.
The new `webpage` module allows us to represent pages as `webpage_t` objects, to fetch a page from the Internet, and to scan a (fetched) page for URLs. 
We also use the `file` and `word` modules for reading and parsing inputs 

## Function prototypes

Detailed descriptions of the functions below are given above, 

```c
index_t* indexFromFile(FILE* indexFile);
void getQueries(index_t* pageIndex, char* pageDir);
char** tokenizeQuery(char* input, int* numWords, char* output);
void normalizeQuery(char** input, int numWords);
void handleQuery(char** input, int numWords, index_t* pageIndex, char* pageDir);
void countersMerge(counters_t* result, counters_t* temp);
void mergeHelper(void* result, const int key, const int tempCount);
void countersIntersect(counters_t* temp, counters_t* new);
void intersectHelper(void* args, const int newKey, const int newCount);
void printQueryResult(counters_t* result, char* pageDir);
void getNumDocs(void* counter, const int docID, const int score);
void getHighestScore(void* argstruct, const int docID, const int score);
```


## Error handling and recovery

All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

If any errors regarding reading files are encountered, the program prints to stderr and quits. 

Other errors with the query that do not terminate the program are printed to stdout. 

## Testing plan

Here is an implementation-specific testing plan.

### Integration/system testing

We write a script `testing.sh` that invokes the querier several times, with a variety of command-line arguments.
First, a sequence of invocations with erroneous arguments, testing each of the possible mistakes that can be made in running the program. 
Second, a sequence of tests that demonstrate correct functionality of the querier over valid arguments and a small index are done to confirm specifically the search mechanism and its respective merge and intersect methods
Third, two (very extensive) fuzz tests are done, one just normally and one with valgrind. 

See the bottom of the file to see that there are no memory leaks. 

