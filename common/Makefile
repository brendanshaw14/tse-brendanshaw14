# Makefile for the common directory
# Builds and compiles files for common
#
# Ashley Goh, Dartmouth CS 50, January 2023

# object files and the target library
#OBJS = pagedir.o ../libcs50/file.o ../libcs50/webpage.o ../libcs50/mem.o
#LIB = common.a

#FLAGS = -lm
#CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
#CC = gcc
#MAKE = make

## build $(LIB) by archiving object files
#$(LIB): $(OBJS)
#ar cr $@ $^

## dependencies: object files depend on header files
#pagedir.o: pagedir.h ../libcs50/webpage.h ../libcs50/file.h
#../libcs50/file.o: ../libcs50/file.h
#../libcs50/webpage.o: ../libcs50/file.h ../libcs50/webpage.h ../libcs50/mem.h
#../libcs50/mem.o: ../libcs50/mem.h

#.PHONY: clean

#clean:
#rm -f core
#rm -f $(LIB) *~ *.o

L = ../libcs50
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L

OBJS = pagedir.o
LIB = common.a 
LIBS = -lm
LLIBS = $L/libcs50-given.a 

.PHONY: clean

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS) $(LLIBS) $(LIBS)

pagedir.o: $L/webpage.h pagedir.h 

clean: 
	rm -rf *.dSYM 
	rm -f common.a 
	rm -f *~ *.o
	rm -f core