# CS50 TSE Querier 
## Design Spec

In this document we reference the requirements spec and focus on the implementation-independent design decisions.

- User interface
- Inputs and outputs
- Functional decomposition into modules
- Pseudo code (plain English-like language) for logic/algorithmic flow
- Major data structures
- Testing plan

## User interface

To run the querier: 

```bash
$ querier pageDirectory indexFile
```

For example, to query my previously created indexFile (indexFileMakeTest) in my data/letters/ pagedirectory, I would run: 

``` bash
$ ./querier ../data/letters ../data/indexFileMakeTest
```

## Inputs and outputs

*Input:* Aside from the command line arguments inputted to the querier above, the querier then takes input from stdin. The querier will prompt the user for a query, then printing the results and asking for the next query. This can also be achieved via pipe. 

*Output:* Per the requirements spec, the querier will test the query for errors, printing the specific errors if errors are found, Otherwise, a list of documents ranked by score (number of times the query matches that document) will be printed in order.

Each search result will be printed in the following format: score (score) doc: (docID) (URL)

## Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules
 2. *indexFromFile*, copied in part from the indexer: returns an index given an indexFile
 3. *getQueries*, which retrieves input lines from stdin, calling methods below on those lines. 
 4. *tokenizeQuery*, which takes the input `char*` line string and parses it into a `char**` pointer array of strings, each holding the words from the line sequentially.
 5. *handleQuery*, which steps through each word of the query and handles it accordingly. 
 6. *normalizeQuery*, which steps through each word of the query and calls `word_normalize` on it. 
 7. *countersMarge*, which takes two input counters of docIDs and their scores and merges them
 8. *mergeHelper*, which is passed to the iterator in `countersMerge` to handle the merge itself.  
 9. *countersIntersect*, which takes two input counters of docIDs and their scores and intersects them
 10. *intersectHelper*, which is passed to the iterateor in `countersIntersect` to carry out the intersect
 11. *printQueryResult*, which takes the final counters that are to be displayed and fetches the appropriate information to print. 
 12. *getNumDocs*, which takes the final counter and iterates through it to find the number of search results with a non-zero score
 13. *getHighestScore*, which takes the final counter and iterates through it to find and save the documentId with the highest score (and the score itself.)

And some helper modules that provide data structures:

  1. *counters* of docID- score pairs that are used throughout the program
  2. *index* - the same as used in indexer. 

## Pseudo code for logic/algorithmic flow

The querier will run as follows:

    validate arguments and file locations
    build the index from the file
    retrieve queries from the stdin
        tokenize the query
        normalize the query
        iterate through each word in the query 
            carry out the appropriate action based on whether it is a word or operator to build the result counters that match the query
        print out those counters in order
        ask for the next query
    

Notice that our pseudocode says nothing about the order in which webpages our displayed- webpages of the same score may appear in any order-- we only guarantee that top scoring pages will be displayed first.

The querier exits when EOF is triggered by the user typing ^D, or by argument or file errors. 

## Major data structures

Helper modules provide all the data structures we need:

- *bag* of webpage (URL, depth) structures
- *index* of words
- *webpage* contains all the data read for a given webpage, plus the URL and the depth at which it was fetched
- *counterArgs* that holds both a temp and a new counters_t* to pass as an argument to the intersect method. 
- *maxDoc* that holds a docID and maxScore of the current highest scoring document to be displayed. 

## Testing plan

A sampling of tests that should be run:

1. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

2. Test the handleQuery method using print statement output to make sure the merge and intersect methods to be written will be called in the correct order

3. Test the program on simple indexes to make sure that the intersect and merge methods work correctly when applied to actual indexes. 

4. Test the program using fuzzquery to make sure no memory leaks or edge cases fail. 
