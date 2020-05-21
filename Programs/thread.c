#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 

void *mythread(void *arg) {
    printf("%s\n", (char *) arg);
    return NULL;
}
int main(int argc, char *argv[]) {                    
    pthread_t p1, p2;
    printf("main: begin\n");
    pthread_create(&p1, null, mythread, "a"); 
    pthread_create(&p2, null, mythread, "b");
    // join waits for the threads to finish
    pthread_join(p1, null); 
    pthread_join(p2, null); 
    printf("main: end\n");
    return 0;
}
