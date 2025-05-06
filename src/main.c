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

            Fifo *tokens = sh_tokenize_line(line);

            void *data = peek(tokens);
            while (data != NULL) {
                printf("Token: [%s]\n", (char *) data);
                dequeue(tokens);
                data = peek(tokens);
            }
            
            free_fifo(tokens);
            free(line);

            return 0;
        }
    }
    else{
        printf("Non-Interactive Mode");
    }
    return 0;
}