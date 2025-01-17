#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int f = fork();
    if (f < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (f == 0) {
	    // child: redirect standard output to a file
    	close(STDOUT_FILENO); 
	    open("./p4-output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

	    // now exec "wc"...
        char *myargs[4];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("redirect.c"); // argument: file to count
        myargs[2] = strdup("example.txt");
        myargs[3] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
    }
    return 0;
}

