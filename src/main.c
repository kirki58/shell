#include <unistd.h>
#include "shell.h"

int main(){
    /*
        Determine if the shell should in interactive mode.
        isatty(STDIN_FILENO) returns 1 if the provided file descriptor (STDIN_FILENO = 0) is a terminal (like a keyboard)

        If we are in interactive mode display a prompt
    */
    if(isatty(STDIN_FILENO)){ 
        printf("--> ");

        char* line = sh_read_line(stdin);
        if(line != NULL){
            printf("Line read: %s\n", line);

            Dynamic_Array *tokens = sh_tokenize_line(line);

            for (size_t i = 0; i < tokens->len; i++)
            {
                printf("Token: [%s]\n", tokens->arr[i]);
            }
            
            free(line);
            free_dynamic_array(tokens);
            
            return 0;
        }
    }
    else{
        printf("Non-Interactive Mode");
    }
    return 0;
}