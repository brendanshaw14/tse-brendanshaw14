/* indexertest.c- reads from an indexer output file and then rebuilds the index from it, then ouputting it back into the file. 
*
* Author: Brendan Shaw- February 2023
* CS50- 23W
* 
* Inputs: stdin- runs through the command line
* Outputs: file output with the rebuilt inverse index to the given file name. 
* 
* Usage
*Compile: `make` using makefile. `make test` for test and `make valgrind` for valgrind test. See makefile for tdetails.

  ****SEE HEADER FILE FOR MORE DETAILS ABOUT FUNCTIONS.**** 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "indexer.h"

index_t* indexFromFile(FILE* fp);

int main(const int argc, char* argv[]){
  if (argc !=3){
    printf("Incorrect number of arguments");
    exit(1);
  }
  //open infile
  FILE* in = fopen(argv[1], "r");
  if (in == NULL){
    printf("Unable to open index infile");
    exit(1);
  }
  //open outfile 
  FILE* out = fopen(argv[2], "w");
  if (out == NULL){
    printf("Unable to open index outfile");
    exit(1);
  }
  //make the index from a page
  index_t* index = indexFromFile(in);
  return 0;
}
/*
 make an index
  for each line in the file
    make a variable to store that word
    make two integers, docID and wordcount
      while fscanf("%d %d", docID, wordcount) ==2
    */
index_t* indexFromFile(FILE* fp){
  index_t* newIndex = index_new(file_numLines(fp));
  char* currentLine; //FREE THIS LATER
  char* word;
  int* docID;
  int* num;
  while ((currentLine = file_readLine(fp)) != NULL && (word = file_readWord(fp)) != NULL){
    printf("Found %s", word);
    while (sscanf(currentLine, "%d %d", docID, num)== 2){
      printf(" %d %d", *docID, *num);
    }
    printf("\n");
  }
  return newIndex;
}
