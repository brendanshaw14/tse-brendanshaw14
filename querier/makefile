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

all: common.a querier fuzzquery 

#makes the common library to actualize changes to pagedir
common.a:
	cd ../common; make

# executable depends on object files
querier: $(OBJS) $(LLIBS) $(CLIBS) 
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) $(LLIBS) $(FLAGS) -o querier

fuzzquery: fuzzquery.o $(LLIBS) $(CLIBS) 
	$(CC) $(CFLAGS) fuzzquery.o $(CLIBS) $(LLIBS) $(FLAGS) -o fuzzquery

# dependencies: object files depend on header files
querier.o: ./querier.c $(LLIBS) $(CLIBS)

fuzzquery.o: ./fuzzquery.c $(LLIBS) $(CLIBS) 


test: 
	bash -v testing.sh

#make valgrind for querier
valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./querier ../data/letters ../data/indexFileMakeTest

fuzz: 
	./fuzzquery ../data/toscrape1Index 100 1 | ./querier /thayerfs/home/f005670/cs50-dev/shared/tse/output/toscrape-1 ../data/toscrape1Index

fuzzgrind: 
	./fuzzquery ../data/toscrape1Index 100 1 | valgrind --leak-check=full --show-leak-kinds=all ./querier /thayerfs/home/f005670/cs50-dev/shared/tse/output/toscrape-1 ../data/toscrape1Index
#fuzzquery indexFile numQueries randomSeed
#cleanup!!
clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f *.core
