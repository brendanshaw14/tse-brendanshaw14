 # Common Directory Makefile
 # Compiles the common directory 
 # Author: Brendan Shaw: with inspiration from Lab3 makefiles & TA's
 #
 # Dartmouth CS50, February 2023
 #
 # Usage: `make` to compile- not needed if running the crawler makefile, which will run this makefile automatically.

#libs and flags
L = ../libcs50
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L
OBJS = pagedir.o index.o word.o
LIB = common.a 
LIBS = -lm
LLIBS = $L/libcs50-given.a 

.PHONY: clean

#common dependencies
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS) $(LLIBS) $(LIBS)

#pagedir dependencies 
pagedir.o: $L/webpage.h pagedir.h 

#index dependencies
index.o: $L/hashtable.h $L/counters.h 

#cleanup
clean: 
	rm -rf *.dSYM 
	rm -f common.a 
	rm -f *~ *.o
	rm -f core