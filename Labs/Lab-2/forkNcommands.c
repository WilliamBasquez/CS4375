#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commands.h"

int main()
{
    char **user_command;
    char *user_input = malloc(1000);
    int start_location;

    while(1){
        printf("> ");
        gets(user_input);
        user_command = get_user_input(user_input);
        
        //If the user wants to change directories
        if (strcmp(user_command[0], "cd") == 0) {
            //If the directory does not exist
            if (changeDir(user_command[1]) < 0) {
                //perror(user_command[1]);
                printf("%s: not a valid directory\n",user_command[1]);
            }
        
            /* if, directory exists, Skip to the fork, and perform the command */
            continue;
        } else if (strcmp(user_command[0], "exit") == 0){ //If the user wants to exit the shell
            if (execvp(user_command[0], user_command) < 0){
                printf("\n\tGoodbye!\n");
                exit(0);
            }
        }
    
        /* If the user wants to execute a different command, aside from 'cd' and 'exit', fork the current process */
        int f = fork();
        if (f == 0){
            //If the command to perform is not valid, give an error message
            if (execvp(user_command[0], user_command) < 0){
                //perror(user_command[0]);
                printf("%s: Invalid command\n",user_command[0]);
            } else //execute command
                execvp(user_command[0], user_command);
        } else { //Wait for the child process
            //wait(NULL);
            waitpid(f, &start_location, WUNTRACED);
        }

        /* At the end of performing the command, free the user input, as well as the command transformed */
        free(user_input);
        free(user_command);
    }

    return 0;
}
