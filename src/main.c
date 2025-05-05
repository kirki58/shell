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

        int n = 0;
        char* line = sh_read_line(stdin, &n);
        if(line != NULL){
            printf("Line read: %s\n", line);
            return 0;
        }
    }
    else{
        printf("Non-Interactive Mode");
    }
    return 0;
}