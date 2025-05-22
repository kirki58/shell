#include <unistd.h>
#include "shell.h"

int main(){
    /*
        Determine if the shell should in interactive mode.
        isatty(STDIN_FILENO) returns 1 if the provided file descriptor (STDIN_FILENO = 0) is a terminal (like a keyboard)

        If we are in interactive mode display a prompt
    */
    if(isatty(STDIN_FILENO)){ 

        while (1)
        {
            printf("$$ "); // Prompt

            char* line = sh_read_line(stdin);
            if(line == NULL){
                if(feof(stdin)){
                    break;
                }
                fprintf(stderr, "Shell failed to read a line from stdin\n");
            }
            else{
                Dynamic_Array *tokens = sh_tokenize_line(line);
                free(line);

                SH_Command *command = sh_parse_tokens(*tokens);
                
                // printf("name: %s\n", command->name);
                // printf("argc: %d\n",command->argc);
                // printf("argv: [");
                // for (int i = 0; i < command->argc; i++)
                // {
                //     printf("%s", command->argv[i]);
                //     if(i != command->argc - 1){
                //         printf(", ");
                //     }
                // }
                // printf("]\n");

                sh_execute_command(*command); 

                free_dynamic_array(tokens);  // now command->name and command->argv are dangling pointers
                command->name = NULL;
                command->argv = NULL;
                free(command);
            }
        }
        return 0;
    }
    else{
        printf("Non-Interactive Mode");
    }
    return 0;
}