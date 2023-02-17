/* Querier.c- the final part of the CS50 TSE Lab. 

Author: Brendan Shaw, February 2023
CS50- Winter 2023

See querier.h for detailed descriptions of methods and functions. 

Usage: ./querier <pageDirectory> <indexFile> 

To use, make test. 
*/

//includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"


/**************** file-local global variables ****************/

/*******************Local Function Headers*******************/
index_t* indexFromFile(FILE* indexFile);
void getQueries(index_t* pageIndex, char* pageDir);
char** tokenizeQuery(char* input, int* numWords, char* output);
bool verifyQuery(char** tokenizedQuery);
void normalizeQuery(char** input, int numWords);
void handleQuery(char** input, int numWords, index_t* pageIndex, char* pageDir);
void countersMerge(counters_t* result, counters_t* temp);
void mergeHelper(void* result, const int key, const int tempCount);
void countersIntersect(counters_t* temp, counters_t* new);
void intersectHelper(void* args, const int newKey, const int newCount);
void printQueryResult(counters_t* result, char* pageDir);
void getNumDocs(void* counter, const int docID, const int score);
void getHighestScore(void* argstruct, const int docID, const int score);
int fileno(FILE *stream);


//verifies correct number of arguments, validates pagedir and indexFile, and calls getquery
int main(const int argc, char* argv[]){
    //check correct num args
    if (argc != 3){
        fprintf(stderr, "Error: Incorrect number of arguments\n");
        exit(1);
    }
    //validate pageDir
    if (pagedir_validate(argv[1]) != true){
        fprintf(stderr, "Error: invalid or nonexistent pageDir\n");
        exit(2);
    }
    //validate indexFile
    FILE* indexFile = NULL;
    indexFile = fopen(argv[2], "r");
    if (indexFile == NULL){
        fprintf(stderr, "Error: Unable to open indexFile\n");
        exit(3);
    }
    //load the index from the indexFile
    index_t* index = indexFromFile(indexFile);
    //get the new queries from the user
    getQueries(index, argv[1]);
    //clean up: delete index and close the file
    index_delete(index);
    fclose(indexFile);
    return 0;
}


//returns a new index holding the information stored in the given indexFile
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
    //free mem
    mem_free(word);
    mem_free(docID);
    mem_free(num);
    return newIndex;
}

//loops through the queries inputted to stdin until EOF, tokenizing them and passing them to handleQuery
void getQueries(index_t* pageIndex, char* pageDir){
    //initial print statement
    printf("Type your search:   ");
    //loop through the query lines
    char* inputLine;
    int* numWords = mem_malloc(sizeof(int));
    while ((inputLine = file_readLine(stdin)) != NULL){
        //if something was typed (as opposed to just enter)
        if (strlen(inputLine)!=0){
            //make space to print the line without spaces into
            char* output = mem_malloc(strlen(inputLine)+1);
            char** tokenizedQuery;
            //call tokenizequery and check that terms were provided, error and get the next query if not
            if ((tokenizedQuery = tokenizeQuery(inputLine, numWords, output)) != NULL){
                //if input isn't from standardin (instead from a pipe), print the input query
                if (!isatty(fileno(stdin))) {
                    printf("%s ", inputLine);
                }
                //normalize the words in the query
                normalizeQuery(tokenizedQuery, *numWords);
                //handle the query
                handleQuery(tokenizedQuery, *numWords, pageIndex, pageDir);
                mem_free(tokenizedQuery);
                mem_free(output);
                *numWords = 0;
            }
            else {
                mem_free(tokenizedQuery);
            }
        }
        //free the current line and ask for the next one
        mem_free(inputLine);
        printf("Type your search:   ");
    }
    //free the rest
    mem_free(inputLine);
    mem_free(numWords);
    return;
}

//takes the input line and returns it as one string with no spaces
char** tokenizeQuery(char* input, int* numWords, char* output){
    //make a new string to put the result into (MAX 200 WORDS); 
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
        else if (currentChar == ' '){
            //if we are coming out of a word, change inword to false and add the terminator
            if (inWord == true){
                (*numWords)++;
                output[charIndex] = '\0';
                charIndex ++;
                inWord = false;
            }
        }
        else {
            printf("Error: invalid character(s) included in search\n");
            return NULL;
        }
         //make sure that the 200 word limit hasn't been passed
        if (*numWords >= 200){
            printf("Error: query word limit (200) exceeded\n");
            return NULL;
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
    //for each word in the query
    for (int i = 0; i < numWords; i ++){
        char* currentWord = word_normalize(input[i]); //create a normalized copy
        strcpy(input[i], currentWord);//copy that copy into the input
        mem_free(currentWord); //then free the copy
    } 
    return;
}

/* Handle the words in the query */
void handleQuery(char** input, int numWords, index_t* pageIndex, char* pageDir){
    //test that neither the first nor last word is and or or
    if ((strcmp(input[0], "and") == 0) || (strcmp(input[0], "or") == 0) || (strcmp(input[numWords-1], "and") == 0) || (strcmp(input[numWords-1], "or") == 0)){
        printf("Error: First and last words of query cannot be operators.\n");
        return;
    }
    int index = 0;
    counters_t* result = counters_new();
    counters_t* temp;
    bool intersect = false;
    //for each word in the query
    while (index < numWords){
        //if the word is and
        if(strcmp(input[index], "and") == 0){
            //make sure the next word isn't also and
            if (strcmp(input[index], input[index+1]) == 0){
                printf( "Error: found two consecutive and operators \n");
                return;
            }
            index ++;
        }
        //if the word is or
        else if (strcmp(input[index], "or") == 0){
            //make sure the next word isn't also and
            if (strcmp(input[index], input[index+1]) == 0){
                printf( "Error: found two consecutive or operators \n");
                return;
            }
            intersect = false;
            // merge result and temp
            countersMerge(result, temp);
            index++;
        }
        //otherwise add the word to temp
        else{
            //if it's the first word of a phrase, change intersect to true and add it to temp
            if (intersect == false){
                intersect = true;
                //add to temp
                temp = hashtable_find(pageIndex -> wordIndex, input[index]);
                index++;
            }
            //if currently being intersected, intersect the word with temp
            else{
                //intersect the word with temp
                counters_t* toIntersect = hashtable_find(pageIndex -> wordIndex, input[index]);
                countersIntersect(temp, toIntersect);
                temp = toIntersect;
                index++;
            }
        }
    }
    countersMerge(result, temp); //merge temp and result
    printQueryResult(result, pageDir); //print the results
    counters_delete(result); //delete the result
    //delete the counters
    return;
}

//merge the counters
void countersMerge(counters_t* result, counters_t* temp){
    //iterate through temp, passing the result counter and applying the mergeHelper
    counters_iterate(temp, result, mergeHelper);
    return;
}

//merge helper-- function that is called upon each item in temp;
// receives temp-> key and temp-> count
//ensures adding of docs and their scores from temp into result
void mergeHelper(void* result, const int tempKey, const int tempCount){
    //if the result doesn't already have that word, add that counter to the value of temp-> count
    if (counters_get(result, tempKey) == 0){
        counters_set(result, tempKey, tempCount);
    }
    //otherwise, retrieve the values of both counters, add them, and set result to the new value
    else{
        counters_set(result, tempKey, counters_get(result, tempKey) + tempCount);
    }
    return;
}

//define the struct to pass as arg into countersIntersect so it can access both temp and new
struct counterArgs {
    counters_t* temp;
    counters_t* new;
};

//intersect the counters
void countersIntersect(counters_t* temp, counters_t* new){
    struct counterArgs counters = {temp, new}; //
    counters_iterate(new, &counters, intersectHelper);
    return;
}

//intersect helper-- function that is called upon each item in temp; receives temp-> key and temp-> count
void intersectHelper(void* args, const int newKey, const int newCount){
    //store the args locally
    struct counterArgs* counters = args;
    int tempCounter;
    //if the result also has the key, find the lesser of their two keys and save that 
    if ((tempCounter = counters_get(counters -> temp, newKey)) != 0){
        if (tempCounter < newCount){
            counters_set(counters -> new, newKey, counters_get(counters -> temp, newKey));
        }
    }
    //otherwise set it to 0 (which will not be printed)
    else{ 
        counters_set(counters -> new, newKey, 0);
    }
    return;
}

//struct to hold both a maxScore and the ID for that max score to find the docId of the maxscore
struct maxdoc {
    int maxScore;
    int ID;
};

//given a counter (result) containing docIDs and their scores
void printQueryResult(counters_t* result, char* pageDir){
    int numMatches = 0;
    //iterate through the result to find the number of matches (pages with a non-zero score)
    counters_iterate(result, &numMatches, getNumDocs);
    //print if no matches were found
    if (numMatches == 0){
        printf("\nNo Matching Documents");
    }
    //if matches were found
    else{ 
        printf("Matches %d documents (ranked):\n", numMatches);
        struct maxdoc max = {0, 0};
        for(int i = 0; i < numMatches; i ++){
            //find the highest score and its docID and store in max
            counters_iterate(result, &max, getHighestScore);
            //open the pagedirFile
            char* pageDirName = mem_malloc(strlen(pageDir) + 10);
            sprintf(pageDirName, "%s/%d", pageDir, max.ID);
            FILE* fp = fopen(pageDirName, "r");
            if (fp == NULL){
                fprintf(stderr, "Unable to open pageDir file %d", max.ID);
                exit(4);
            }
            char* URL = file_readLine(fp);
            //print that document
            printf("\nscore   %d doc  %d: %s", max.maxScore, max.ID, URL);
            //set the current highest counter to 0 and reset args
            counters_set(result, max.ID, 0);
            max.ID = 0;
            max.maxScore = 0;
            mem_free(pageDirName);
            mem_free(URL);
            fclose(fp);
        }
    }
    printf("\n_____________________________________\n");
    return;
}
//stores the number of docIDs with a non-zero score in numMatches
void getNumDocs(void* counter, const int docID, const int score){
    int* count = counter;
    if (score != 0){
        (*count) ++;
    }
    return;
}

//sets the input arg to the key of the highest scoring doc
void getHighestScore(void* argstruct, const int docID, const int score){
    struct maxdoc* args = argstruct;
    //if the score is higher, then set that to the new score and save its docID
    if (score > args -> maxScore){
        args -> maxScore = score;
        args -> ID = docID;
    }
    return;
}