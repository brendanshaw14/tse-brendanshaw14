#CS50 LAB 4
##CS50 23W

### Pagedir
In summary a program supplemental to the crawler that assists in creating the .crawler signature in the pagedirectory and in writing new files with website info into them.

The `pagedir` program includes a `pagedir.h` header file and a `Makefile` for usage. See the `pagedir.h` header for more info. 

```c
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
```

### Assumptions
No major assumptions were made. The pagedir module functions just like the implementation spec, and has no known errors. 

### Files
* `Makefile` - compilation procedure and testing
* `pagedir.h` - the header file 
* `pagedir.c` - the program

### Compilation

To compile, `make`, or `make` in the crawler directory.

