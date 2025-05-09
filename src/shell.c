#include "shell.h"

char *sh_read_line(FILE *stream){
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
        return line; // Free line after done using it to prevent memory leaks!
    }
}

Dynamic_Array *sh_tokenize_line(const char *line)
{
    const char *p = line;
    const char* start = line; // Set the start pointer (To be used inside the loop)
    Dynamic_Array *tokens = init_dynamic_array(DEFAULT_TOKEN_COUNT);

    do
    {
        // When current character is whitespace, skip the character 
        while (isspace(*p)){p+=sizeof(char);} // Skip extra white spaces

        if(p != line && isspace(*(p - sizeof(char))) ){ // Encountered a regular character after white space character (start of a token), and we are not in the first iteration
            start = p;
        }
        while(!isspace(*p) && *p != '\0' ){p+=sizeof(char);} // Skip all regular characters, skip to the next white space

        size_t size_ch = p - start;
        char token[size_ch + 1]; // p - start = no. of read characters, including the last white space, which should be replaced by '\0'
        
        strncpy(token, start, size_ch);
        token[size_ch] = '\0';
        
        dynamic_array_push(tokens, token); // Put the obtained token in the dynamic array, + 1 accounts for null terminator because it's not counted by strlen
        
        if(*p != '\0'){
            p+=sizeof(char);
        }
    } while (*p != '\0');

    return tokens;
}