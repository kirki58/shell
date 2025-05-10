#ifndef SHELL_H
#define SHELL_H

/* 
    shell.h - Core functions for the basic shell
    --------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "dynamic_array.h"

#define DEFAULT_TOKEN_COUNT 10 // Used as a initial size while initialazing the tokens dynamic array.

typedef struct sh_command{
    char* name;     // name of the command e.g. "ls" or "/bin/ls", basically the first token in the tokens array
    char** argv;    // argv, tokens themselves
    int argc;
}SH_Command;

/* 
    sh_read_line reads a line from a file stream and writes it into a buffer
    n is a pointer to a passed in integer, where it will write the number of characters read from the line.
    
    Returns:
        The buffer containing the read line on success
        NULL on failure
*/
char *sh_read_line(FILE *stream);

/*
    sh_tokenize_line tokenizes a given string (line) into tokens and puts them inside a queue.

    Returns:
        A queue storing the tokens obtained from the line.
*/
Dynamic_Array *sh_tokenize_line(const char* line);
#endif