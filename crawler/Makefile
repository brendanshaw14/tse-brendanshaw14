# Makefile for Crawler 
# 
# Brendan Shaw, February 2020. 
# CS50 23W

#object files and target library
C = ../common
L = ../libcs50
OBJS = crawler.o
LLIBS = $L/libcs50.a $C/common.a
FLAGS = -lm
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
MAKE = make

# executable depends on object files
crawler: crawler.o $(LLIBS) 
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

#dependencies
cralwer.o: crawler.h $C/pagedir.h $L/hashtable.h $L/bag.h $L/webpage.hashtable
crawler.o: $L/mem.h

#valgrind target
valgrind: crawler 
	cd ../common/; make; cd ../crawler/;
	$(VALGRIND) ./testing.sh 

test: crawler
	./testing.sh

clean: 
	rm -f core
	rm -f(LIB) *~ *.o
