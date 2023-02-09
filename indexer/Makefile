 # Crawler Makefile
 # Compiles the crawler as well as the common folder with pagedir.c and pagedir.h in it. 
 # Author: Brendan Shaw: with inspiration from Lab3 makefiles & TA's
 #
 # Dartmouth CS50, February 2023
 #
 # Usage: `make` to compile, then `make test` to run test file or `make valgrind` for testing with Valgrind. 

#libs and objects
L = ../libcs50
C = ../common
OBJS = indexer.o
LIB = common.a

#flags & other
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
LLIBS = $L/libcs50.a
CLIBS = $C/common.a
FLAGS = -lm

.PHONY: all clean test

all: common.a indexer 

#makes the common library to actualize changes to pagedir
common.a:
	cd ../common; make

# executable depends on object files
indexer: $(OBJS) $(LLIBS) $(CLIBS) 
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) $(LLIBS) $(FLAGS) -o indexer

# dependencies: object files depend on header files
indexer.o: ./indexer.c $(LLIBS) $(CLIBS)

# make test for this //test: 
test: 
	./indexer ../data/letters ../data/indexFileMakeTest
#make valgrind for this
valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./indexer ../data/letters ../data/indexFileMakeTest
#cleanup!!
clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f *vgcore
	rm -f ../data/indexFileMakeTest
