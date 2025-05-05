#ifndef SHELL_H
#define SHELL_H

/* 
    shell.h - Core functions for the basic shell
    --------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

/* 
    sh_read_line reads a line from a file stream and writes it into a buffer
    n is a pointer to a passed in integer, where it will write the number of characters read from the line.
    
    Returns:
        The buffer containing the read line on success
        NULL on failure
*/
char *sh_read_line(FILE *stream, int *n);

/*
    sh_parse_line parses a given string (line) into meaningful tokens.
    n is the number of characters in that line (which can be obtained from sh_read_line)

    Returns:
        A queue storing the tokens parsed from the line.
*/
Fifo *sh_parse_line(char* line, int n);
#endif