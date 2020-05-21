#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

//Run code in a loop
//TIME!!

int main(int argc, char *argv[]) {
    printf("Hello world! (pid%d)\n", (int)getpid());
    int rc = fork();
    if(rc < 0){ //fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) { //child (new process)
        printf("Hello, I am child (pid:%d)\n", (int)getpid());
        sleep(1);
    } else{ //parent goes down this path(main)
      int rc_wait = wait(NULL);
      printf("Hello, I am parent of %d (rc_wait:%d)(pid:%d)\n", rc, rc_wait, (int)getpid());
      sleep(20);
    }
    return 0;
}
