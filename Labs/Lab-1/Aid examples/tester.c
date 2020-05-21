#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "read_input.h"
#include "write_output.h"

int main()
{
    func();
    return 0;
}

int func () {
    int my_pipe[2];
    pipe(my_pipe);
    int p = fork();
    if(p < 0){ //fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (p > 0){ // parent    
        close(my_pipe[0]);
        // close the read side. parent only writes
        write(my_pipe[1], "some string from parent", 24);
        fflush(my_pipe[1]);
        close(my_pipe[1]);
        sleep(1);
    } else{ // child process
        close (my_pipe[1]);
        char input_str[100];
        read(my_pipe[0], input_str, 100);
        close(my_pipe[0]);
        exit (0);
    }
}
