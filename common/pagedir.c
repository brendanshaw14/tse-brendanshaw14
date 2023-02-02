/* Header file for pagedir.c,

Author: Brendan Shaw */

#include <stdlib.h>
#include <stdio.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include <string.h>

bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);


bool pagedir_init(const char* pageDirectory){
    char* newDir = mem_malloc(strlen(pageDirectory)+10);
    strcpy(newDir, pageDirectory);
    strcat(newDir, "/.crawler");
    FILE* fp = fopen(newDir, "r");
    if (fp == NULL){
        printf("Error: pagedir_init unable to create file");
        mem_free(newDir);
        return false;
    }
    free(newDir);
    fclose(fp);
    return true; 
}


void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
    int docIDString_len = snprintf(NULL, 0, "%d", docID);
    char* docIDString = mem_malloc(docIDString_len + 1);
    sprintf(docIDString, "%d", docID);
    char* newDir = malloc(strlen(pageDirectory) + docIDString_len + 2);
    sprintf(newDir, "%s/%s", pageDirectory, docIDString);

    FILE* fp = fopen(newDir, "w");
    if (fp == NULL){
        printf("Error: pagedir_save unable to create file");
        mem_free(newDir);
        mem_free(docIDString);
        return;
    }
    //print URL 
    fprintf(fp, "URL: %s\n", webpage_getURL(page));
    //print depth
    fprintf(fp, "Depth: %d\n", webpage_getDepth(page));
    //print contents
    fprintf(fp, "%s", webpage_getHTML(page));

    fclose(fp);
    return;
}

