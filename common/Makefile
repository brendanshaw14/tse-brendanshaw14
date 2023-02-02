# Makefile for the TSE Common directory
# Builds and compiles the "common" library
#
#
# Brendan Shaw, February 2023 


#object files
L = ../libcs50
OBJS = pagedir.o
LIB = common.a 
LLIBS = $L/libcs50.a
FLAGS = -lm
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc 
MAKE = make 

#build $(LIB) by archiving object files
$(LIB): $(OBJS) $(LLIBS)
	ar cr $@ $^

#Dependencies: object files depend on header files
pagedir.o: pagedir.h $L/mem.h $L/webpage.h

#clean up
clean: 
	rm -f core
	rm -f(LIB) *~ *.o