 # Querier Makefile
 # Compiles the querier as well as the common folder with pagedir.c and pagedir.h in it. 
 # Author: Brendan Shaw 
 #
 # Dartmouth CS50, February 2023
 #
 # Usage: `make` to compile, then `make test` to run test file or `make valgrind` for testing with Valgrind. 

#libs and objects
L = ../libcs50
C = ../common
OBJS = querier.o
#TESTOBJS = indextest.o
LIB = common.a

#flags & other
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
LLIBS = $L/libcs50.a
CLIBS = $C/common.a
FLAGS = -lm

.PHONY: all clean test

all: common.a querier  

#makes the common library to actualize changes to pagedir
common.a:
	cd ../common; make

# executable depends on object files
querier: $(OBJS) $(LLIBS) $(CLIBS) 
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) $(LLIBS) $(FLAGS) -o querier

# dependencies: object files depend on header files
querier.o: ./querier.c $(LLIBS) $(CLIBS)

#querier.o: ./indextest.c $(LLIBS) $(CLIBS)

test: 
	./querier ../data/letters ../data/indexFileMakeTest

#make valgrind for indexer
valgrind: 

#cleanup!!
clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f *vgcore
