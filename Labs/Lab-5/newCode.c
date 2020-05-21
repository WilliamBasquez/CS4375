#include <stdio.h>
#include <time.h>
#include <math.h>
#define TRUE 1
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

char bufferA[1000], bufferB[1000];
char *toA = NULL, *toB = NULL;
struct timeval start;
sem_t lock;
pthread_t PA, RA, PB, RB, C;

void *threadPA(void);
void *threadRA(void);
void *threadPB(void);
void *threadRB(void);
void write_data(char*);
void *consumeMethod(void);
void gen_new_data(char *,int, char*);
void produceMethod(int,long,long,char*);

int main(){
    pthread_create(&C, NULL, (void*)consumeMethod, NULL);

    sem_init(&lock, 1, 1);
	
    pthread_create(&PA, NULL, (void*)threadPA, NULL);
    pthread_create(&RA, NULL, (void*)threadRA, NULL);
    pthread_create(&PB,NULL, (void*)threadPB, NULL);
    pthread_create(&RB,NULL, (void*)threadRB, NULL);

    pthread_join(PA, NULL);
    pthread_join(RA, NULL);
    pthread_join(PB, NULL);
	pthread_join(RB, NULL);
	
	return 0; 
}

void* threadPA(void){ 	 
  produceMethod(1, 1L, 1000000L, "pa");
}

void* threadPB(void){ 
	produceMethod(1, 1L, 1000000L, "pb");
}

void* threadRA(void){ 
	produceMethod(0, 1.5L,  150000000L, "ra");
}

void* threadRB(void){
	produceMethod(0, 1.5L,  150000000L, "rb");
}

void produceMethod(int isPrime, long secDelay, long nsecDelay, char *producer){
  gettimeofday(&start,0);

  while(TRUE){
    struct timespec t1, t2;
    t1.tv_sec = secDelay;
    t1.tv_nsec = nsecDelay; 
    
    //Take care of threads for AP and AR
    if(strcmp(producer, "pa") || strcmp(producer, "ra")){
      nanosleep(&t1, &t2);
      gen_new_data(bufferA, isPrime, producer);
      write_data(bufferA);
    }

    //Take care of threads for BP and BR
    if(strcmp(producer, "pb") || strcmp(producer, "rb")){
      nanosleep(&t1, &t2);
      gen_new_data(bufferB, isPrime, producer);
      write_data(bufferB);
    }
  }
}

void gen_new_data(char *buffer, int isPrime, char *producer) {
    struct timeval now;
    gettimeofday (&now, 0);
    double delta = (now.tv_sec - start.tv_sec) + (double)(now.tv_usec - start.tv_usec)/1000000L;

    if(isPrime && buffer[0] == '\0'){ 
        if(strcmp(producer, "pa") || strcmp(producer, "ra"))
            sprintf(buffer,"AP: %3.2f", sin(delta));
        
        else if(strcmp(producer, "pb") || strcmp(producer, "rb"))
            sprintf(buffer,"BP: %3.2f", sin(delta));

    } else if(isPrime == 1){
        if(buffer[0] == '\0'){
            if(strcmp(producer, "pa") || strcmp(producer, "ra"))
                sprintf(buffer,"AR: %3.2f", sin(delta));
        
            else if(strcmp(producer, "pb") || strcmp(producer, "rb"))
                sprintf(buffer,"BR: %3.2f", sin(delta));

            else if(strcmp(producer, "pa") || strcmp(producer, "ra"))
                printf("%6.3f\tAR: %3.2f \t \n", delta, sin(delta));

            else if(strcmp(producer, "pb") || strcmp(producer, "rb"))
                printf("%6.3f\tBR: %3.2f\n", delta, sin(delta));
        }
    }
}

void write_data(char *buffer) {
    sem_wait(&lock);
    sprintf(buffer, "%s", buffer);
    sem_post(&lock);
}

void *consumeMethod(){
    struct timeval current;
    while (TRUE) {
        char channelA[1000], channelB[1000];
        toA = bufferA;
        toB = bufferB;
        usleep(1500000);
        gettimeofday (&current,0);
        double degree = (current.tv_sec - start.tv_sec) + (double)(current.tv_usec - start.tv_usec)/1000000L;

        sem_wait(&lock);

        if(bufferA[0] != '\0' && bufferB[0] != '\0'){
            strcpy(channelA, bufferA);
            strcpy(channelB, bufferB);
            printf("\nCONSUMER OBTAINED:\n");
            printf("%6.3f\t%s & %s\n\n", degree, channelA, channelB);
            //memset(bufferA, 0 , 1000);
            //memset(bufferB, 0 , 1000);
            toA = NULL;
            toB = NULL;
        }
        sem_post(&lock);
    }
}
