/* Header file for pagedir.c,

Author: Brendan Shaw */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include <string.h>

bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);


bool pagedir_init(const char* pageDirectory){
    char* newDir = mem_malloc(strlen(pageDirectory)+10);
    sprintf(newDir, "%s/.crawler", pageDirectory);

    FILE* fp = fopen(newDir, "w");
    if (fp == NULL){
        printf("Error: pagedir_init unable to create file");
        mem_free(newDir);
        return false;
    }
    mem_free(newDir);
    fclose(fp);

    return true; 
}


void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
    int docIDString_len = log10(docID) + 1; 
    char* newDir = malloc(strlen(pageDirectory) + docIDString_len + 2);
    sprintf(newDir, "%s/%d", pageDirectory, docID);

    FILE* fp = fopen(newDir, "w");
    //print webpage to file
    fprintf(fp, "%s\n%d\n%s\n", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
    mem_free(newDir);
    fclose(fp);
    return;
}

