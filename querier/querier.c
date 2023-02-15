/* Querier.c- the final part of the CS50 TSE Lab. 

Author: Brendan Shaw, February 2023
CS50- Winter 2023

*/

//includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"

//headers
index_t* indexFromFile(FILE* indexFile);
void getQueries(index_t* pageIndex);
char** tokenizeQuery(char* input, int* numWords, char* output);
bool verifyQuery(char** tokenizedQuery);
void normalizeQuery(char** input, int numWords);
void handleQuery(char** input, int numWords, index_t* pageIndex);


//  ./querier pageDirectory indexFileName
/*  validate pageDir using pagedir_valdiate
    validate indexfile by open attempt in read
    call indexFromFile on the indexFile
    pass that index to getQueries         
*/

int main(const int argc, char* argv[]){
    //check correct num args
    if (argc != 3){
        printf("Error: Incorrect number of arguments\n");
        exit(0);
    }
    //validate pageDir
    if (pagedir_validate(argv[1]) != true){
        printf("Error: invalid or nonexistent pageDir\n");
        exit(0);
    }
    //validate indexFile
    FILE* indexFile = NULL;
    indexFile = fopen(argv[2], "r");
    if (indexFile == NULL){
        printf("Error: Unable to open indexFile\n");
    }
    index_t* index = indexFromFile(indexFile);
    //get the new queries from the user
    getQueries(index);
   
    return 0;
}


//returns a new index holding the information stored in the given indexFile
/* Pseudo: 
    Make a new index
    loop through words in the file
        scan the ints that follow
        for each pair
            save that pair into the index
    return the new index
*/

index_t* indexFromFile(FILE* indexFile){
    //new index
    index_t* newIndex = index_new(file_numLines(indexFile));
    char* word;
    int* docID = malloc(sizeof(int));
    int* num = malloc(sizeof(int));
    //loop through words in the file
    while ((word = file_readWord(indexFile)) != NULL){
        //pull pairs of numbers after each word until it can't find two 
        while(fscanf(indexFile, "%d %d", docID, num) == 2){
            for (int i = 0; i < *num; i ++){
                //save that pair
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

//loops through the queries inputted to stdin until there
// are no longer queries, calling parseQuery on each line
/* Pseudocode: 
    get each line
    tokenize it
    call verifyQuery
        if true
            call parse query
*/
void getQueries(index_t* pageIndex){
    //initial print statement
    printf("Type your search below:\n");
    //loop through the query lines
    char* inputLine;
    int* numWords = mem_malloc(sizeof(int));
    while ((inputLine = file_readLine(stdin)) != NULL){
        char* output = mem_malloc(strlen(inputLine)+1);
        char** tokenizedQuery;
        tokenizeQuery(inputLine, numWords, output);
        if ((tokenizedQuery = tokenizeQuery(inputLine, numWords, output)) == NULL){
            printf("Error: no search terms provided");
        }
        normalizeQuery(tokenizedQuery, *numWords);
        //handle the query
        handleQuery(tokenizedQuery, *numWords, pageIndex);
        mem_free(inputLine);
        *numWords = 0;
    }
    mem_free(inputLine);
    mem_free(numWords);
    
    return;
}

//takes the input line and returns it as one string with no spaces
char** tokenizeQuery(char* input, int* numWords, char* output){
    //make a new string to put the result into 
    char** outputArray = mem_malloc(200);
    bool inWord = false;
    int charIndex = 0;
    *numWords = 0;
    //for each character
    for (int i = 0; i < strlen(input); i ++){
        char currentChar = input[i];
        //if that character is a letter
        if ((currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z')){
           //if we haven't yet found a word, change inWord to true, add that letter to the new string
            if (inWord == false){
                output[charIndex] = currentChar;
                outputArray[*numWords] = &output[charIndex];
                charIndex++;
                inWord = true;
            }
            //if we are already within a word, add to the new string. 
            else{
                output[charIndex] = currentChar;
                charIndex++;
            }
        }
        //if that character is a space
        if (currentChar == ' '){
            //if we are coming out of a word, change inword to false and add the terminator
            if (inWord == true){
                (*numWords)++;
                output[charIndex] = '\0';
                charIndex ++;
                inWord = false;
            }
        }

    }
    //if the for loop ends while in a word, terminate the word and increment wordcount
    if (inWord == true){
        output[charIndex] = '\0';
        (*numWords)++;
    }
    return outputArray;
}

/* normalize all the words in the query array*/
void normalizeQuery(char** input, int numWords){
    for (int i = 0; i < numWords; i ++){
        input[i] = word_normalize(input[i]);
    } 
    return;
}

/* Handle the words in the query */
void handleQuery(char** input, int numWords, index_t* pageIndex){
    //test that neither the first nor last word is and or or
    if ((strcmp(input[0], "and") == 0) || (strcmp(input[0], "or") == 0) || (strcmp(input[numWords-1], "and") == 0) || (strcmp(input[numWords-1], "or") == 0)){
        printf("Error: First and last words of query cannot be operators. Try again.\n");
    }
    //for each word in the query
    int index = 0;
    counters_t* result = counters_new();
    counters_t* temp = counters_new();
    bool inAnd = false;
    while (index < numWords){
        countersMerge(temp, )
        //if the word is and
        if (strcmp(input[index], "and") == 0){
            //make sure the next word isn't also and
            if (strcmp(input[index], input[index+1]) == 0){
                printf("Error: found two consecutive and operators \n");
            }
            inAnd = true;
            while (inAnd == true){
                
            }
        }
        //if the word is or
        if (strcmp(input[index], "or") == 0){
            //make sure the next word isn't also and
            if (strcmp(input[index], input[index+1]) == 0){
                printf("Error: found two consecutive or operators \n");
            }
            inAnd = true;
            while (inAnd == true){
               if (in) 
            }
        }
        index++;
    }





    return;
}

//merge the counters
void countersMerge(counters_t* first, counters_t* second){
    return;
}

//intersect the counters
void countersIntersect(counters_t* first, counters_t* second){
    return;
}