#include "shell.h"

char *sh_read_line(FILE *stream, int *n){
    char* line = NULL;
    size_t buf_size = 0;

    /*
        get_line will dynamically allocate and resize the buffer for line
        returns -1 on failure or when encountered EOF (might be caused by a signal like CTRL+D)
        returns the no. of characters read on success.
    */
    int res = getline(&line, &buf_size, stream);

    if(res == -1){
        free(line);
        return NULL;
    }
    else{
        *n = res;
        return line; // Free line after done using it to prevent memory leaks!
    }
}