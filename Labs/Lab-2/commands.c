#include <stdlib.h>
#include <string.h>

int changeDir(char*);

/* Function that takes in a pointer containing string(s) symbolizing a command, and executes given command */
char **get_user_input(char *in)
{
    char **newCommand = malloc(1000 * sizeof(char *));
    char *extraChars = " \t\r\n\a";
    char *tokens;
    int index = 0;

    //If allocation of memory fails
    if(newCommand == NULL){
        perror("Allocation failed\n");
        exit(1);
    }

    //turn input "command" into an array of tokens
    tokens = strtok(in, extraChars);
    while (tokens != NULL){
        newCommand[index] = tokens;
        index++;

        tokens = strtok(NULL, extraChars);
    }
    //Terminate the array with the null value
    newCommand[index] = NULL;

    return newCommand;
}

/* Simple function that changes directory given a path to said directory*/
int changeDir(char *path)
{
    return chdir(path);
}
