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
#include <sys/types.h>
#include <sys/wait.h>
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

/*
    sh_parse_tokens parses the given tokens obtained from sh_tokenize_line to a SH_Command struct.

    Returns:
        The buffer containing the parsed SH_Command
        NULL on failure
*/
SH_Command *sh_parse_tokens(Dynamic_Array tokens);

/*
    sh_execute_command - Executes a given command

    sh_execute_command forks the current (shell) process, and replaces the process image of the child process according to the context of the given command
    uses fork() and execvp() system calls

    Returns:
        an exit status
*/
int sh_execute_command(SH_Command command);

#endif