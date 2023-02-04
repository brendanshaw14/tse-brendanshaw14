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
OBJS = crawler.o
LIB = common.a

#flags & other
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
LLIBS = $L/libcs50.a
CLIBS = $C/common.a
FLAGS = -lm

.PHONY: all clean test

all: crawler $L/libcs50.a $C/common.a

#makes the common library to actualize changes to pagedir
common.a:
	cd ../common; make

# executable depends on object files
crawler: $(OBJS) $(LLIBS) $(CLIBS) common.a
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(CLIBS) $(FLAGS) -o crawler

# dependencies: object files depend on header files
crawler.o: ./crawler.c $L/file.h $L/webpage.h $L/mem.h $C/pagedir.h $L/bag.h $L/hashtable.h $L/set.h $L/hash.h

# make test for this 
test: 
	./crawler HTTP://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 10

#make valgrind for this
valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./crawler HTTP://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 10

#cleanup!!
clean:
	rm -f crawler
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f *vgcore
	rm -f ../data/letters/*
	rm -f ../data/letters/.crawler
