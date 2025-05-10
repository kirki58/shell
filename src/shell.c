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

    if(tokens == NULL){
        return NULL;    // Terminate if failed to initialize tokens array
    }

    do
    {
        // When current character is whitespace, skip the character 
        while (isspace(*p)){p+=sizeof(char);} // Skip extra white spaces
        if(*p == '\0'){
            break;  // Skip the rest of the loop if '\0' is after white spaces
            /*
            Example on what this condition avoids: 
            "--> Hello Wolrd    \0"
            Without this condition the tokens would be: ["Hello\0"], ["World\0"], ["\0"]
            */
        }

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

    dynamic_array_equalize(tokens, DYNAMIC_ARRAY_FINALIZE);
    return tokens;
}

SH_Command *sh_parse_tokens(Dynamic_Array *tokens){
    SH_Command *command = (SH_Command*) malloc(sizeof(SH_Command));
    if(command == NULL){
        return NULL;
    }

    command->argv = tokens->arr;
    command->name = tokens->arr[0];
    command->argc = tokens->len - 1; // Assuming the array is a finalized one, the last element of the array would be NULL

    return command;
}
