 #Crawler Makefile
 #Builds and compiles crawler and test
 #Brendan Shaw, Dartmouth CS50, February 2023


L = ../libcs50
C = ../common
OBJS = crawler.o
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
LLIBS = $L/libcs50.a
CLIBS = $C/common.a
FLAGS = -lm

.PHONY: all clean test

all: crawler $L/libcs50.a $C/common.a

common.a:
	cd ../common; make

# executable depends on object files
crawler: $(OBJS) $(LLIBS) $(CLIBS) common.a
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(CLIBS) $(FLAGS) -o crawler

# dependencies: object files depend on header files
crawler.o: ./crawler.c $L/file.h $L/webpage.h $L/mem.h $C/pagedir.h $L/bag.h $L/hashtable.h $L/set.h $L/hash.h

test: 
	./crawler HTTP://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2

valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./crawler HTTP://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2

clean:
	rm -f crawler
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f *vgcore

#L = ../ibcs50
#P = ../common
#CC = gcc
#CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$P -DAPPTEST

#OBJS = crawler.o
#LIBS = -lm
#LLIBS = $L/libcs50-given.a $P/common.a 

#.PHONY: test clean

#crawler: $(OBJS) $(LLIBS)
#$(CC) $(CFLAGS) $^ $(LIBS) -o $@

#crawler.o: $L/webpage.h $L/bag.h $L/hashtable.h $P/pagedir.h

#test: 
#./crawler HTTP://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2	

#clean: 
#rm -rf *.dSYM 
#rm -f common.a 
#rm -f *~ *.o
#rm -f core