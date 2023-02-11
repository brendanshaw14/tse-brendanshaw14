/* indextest.c- reads from an indexer output file and then rebuilds the index from it, then ouputting it back into the file. 
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

index_t* indexFromFile(FILE* in);

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
  index_print(index, out);
  index_delete(index);
  fclose(out);
  fclose(in);
  return 0;
}

//creates an index from the given indexer output file
index_t* indexFromFile(FILE* in){
  index_t* newIndex = index_new(file_numLines(in));
  char* word;
  int* docID = malloc(sizeof(int));
  int* num = malloc(sizeof(int));
  while ((word = file_readWord(in)) != NULL){
      while(fscanf(in, "%d %d", docID, num) == 2){
        for (int i = 0; i < *num; i ++){
          index_save(newIndex, word, *docID);
        }
      }
      mem_free(word);
  }
  mem_free(word);
  mem_free(docID);
  mem_free(num);
  return newIndex;
}
