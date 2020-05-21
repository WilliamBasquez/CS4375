#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main() 
{ 
    int my_pipe[2];  // Used to store two ends of pipe
    pipe(my_pipe);
  
    int p; 
  
    //scanf("%s", input_str);
    p = fork(); 
  
    if (p < 0) { 
        fprintf(stderr, "fork Failed" ); 
        exit(0); 
    } else if (p > 0) { // Parent process
        char user_str[100]; 
  
        //Close the read side, parent only writes
        close(my_pipe[0]);
  
        // Write input string and close writing of pipe.
        write(my_pipe[1], "a", 2);
        fflush(my_pipe[1]);
        
        //Close the write side
        close(my_pipe[1]);

        //Wait for child process
        wait(NULL);
  
        //Read string from child, print it and close reading end. 
        read(my_pipe[1], in_str, 100);
        close(my_pipe[1]);
    } 
  
    else { // child process 
        // Close writing end of pipe 
        close(my_pipe[1]);
  
        // Read a string using first pipe 
        char in_str[100];
        read(my_pipe[0], in_str, 100);
    
        // Close reading end
        close(my_pipe[0]); 
  
        // Write string and close writing end 
        write(my_pipe[1], in_str, strlen(in_str)+1); 
        close(my_pipe[1]);
        exit(0); 
	}
    printf("Here\n");
}

int fun(int argc, char *argv[])
{

    int pipefd[2];
    pid_t cpid;
    char buf;
    if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Child reads from pipe */
        close(pipefd[1]);          /* Close unused write end */
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {            /* Parent writes argv[1] to pipe */
        close(pipefd[0]);          /* Close unused read end */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          /* Reader will see EOF */
        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}
