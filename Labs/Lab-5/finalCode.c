#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "functions.c"

sem_t lock;
pthread_t PA, RA, PB, RB, C;

void *threadPA(void);
void *threadRA(void);
void *threadPB(void);
void *threadRB(void);

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
