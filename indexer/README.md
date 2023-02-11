#CS50 LAB 5
##CS50 23W

### Indexer

An `indexer` takes a pagedirectory input and creates an inverted index word structure.

### Usage

See header files and the implementation spec for a detailed description. 
Run- see indexer.c comments for description. 


### Assumptions
No major assumptions were made. The indexer functions just like the implementation spec. 

Note that the indexer will AUTOMATICALLY CREATE ITS OUTPUT FILE. 

### Files
* `Makefile` - compilation procedure and testing
* `indexer.h` - the header file 
* `indexer.c` - the program
* `testing.sh` - the testfile
* `testing.out` - the result of `bash -v testing.sh &> testing.out`
* `index.h` - index module header
* `index.c` - index module
* `word.c` - word module
* `word.h` - word module header
* `indextest.h` - index test header 
* `indextest.c` - index test 

### Compilation

To compile, `make`. 

### Testing 

`ake test &> testing.out` runs test file, which carries out a variety of tests showing the use of indexer and indextest.  
See `testing.out` for test output. 
For valgrind, `myvalgrind ./crawler`. 
