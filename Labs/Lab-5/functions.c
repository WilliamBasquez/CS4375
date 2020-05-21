#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#define TRUE 1

void write_data(char*);
void *consumeMethod(void);
void gen_new_data(char *,char, char*);
void produceMethod(int, long, long, char*);
void cleanBuffer(char *);

sem_t lock;
struct timeval start;
char bufferA[1000], bufferB[1000];

void produceMethod(int isPrime, long secDelay, long nsecDelay, char *producer){
    gettimeofday(&start,0);

    while(TRUE){
        struct timespec t1, t2;
        t1.tv_sec = secDelay;
        t1.tv_nsec = nsecDelay; 
    
        if(strcmp(producer, "pa") || strcmp(producer, "ra")){
            nanosleep(&t1, &t2);
            gen_new_data(bufferA, isPrime, producer);
            write_data(bufferA);
        }

        if(strcmp(producer, "pb") || strcmp(producer, "rb")){
            nanosleep(&t1, &t2);
            gen_new_data(bufferB, isPrime, producer);
            write_data(bufferB);
        }
    }
}

void gen_new_data(char *buffer, char isPrime, char *producer) {
    struct timeval now;
    gettimeofday (&now, 0);
    double delta = (now.tv_sec - start.tv_sec) + (double)(now.tv_usec - start.tv_usec)/1000000L;

    if(isPrime){
        if(strcmp(buffer,"") == 0){ 
            if(strcmp(producer, "pa")){
                printf("%6.3f \t PA: %3.2f\n", delta, sin(delta));
                sprintf(buffer,"PA: %3.2f", sin(delta));
            }
        }
        
        if(strcmp(producer, "pb")){
            printf("%6.3f \t PB: %3.2f\n", delta, sin(delta));
            sprintf(buffer,"PB: %3.2f", sin(delta));
        }
    } 
    
    else if(!isPrime){
        if(strcmp(buffer,"") == 0){ 
            if(strcmp(producer, "ra")){
                printf("%6.3f\tRA: %3.2f\n", delta, sin(delta));
                sprintf(buffer,"RA: %3.2f", sin(delta));
            }

            if(strcmp(producer, "rb")){
                printf("%6.3f\tRB: %3.2f\n", delta, sin(delta));
                sprintf(buffer,"RA: %3.2f", sin(delta));
            }
        }
    }
}

void write_data(char *channel) {
    sem_wait(&lock);
    sprintf(channel, "%s", channel);
    sem_post(&lock);
}

void *consumeMethod(){
    struct timeval current;
    while (TRUE) {
        char channelA[1000], channelB[1000];
        gettimeofday (&current,0);
        double delta = (current.tv_sec - start.tv_sec) + (double)(current.tv_usec - start.tv_usec)/1000000L;

        sem_wait(&lock);

        if((strcmp(bufferA,"") != 0) && (strcmp(bufferB, "") != 0)){
            printf("\nCONSUMER OBTAINED:\n");
            strcpy(channelA, bufferA);
            strcpy(channelB, bufferB);
            printf("%6.3f\t%s & %s\n\n", delta, channelA, channelB);
            char *tempA = bufferA;
            char *tempB = bufferB;
            cleanBuffer(tempA);
            cleanBuffer(tempB);
        }
        sem_post(&lock);
    }
}

void cleanBuffer(char *b){
    int i;
    for(i = 0; i < 1000; i++)
        b[i] = 0;
}
