#include <stdio.h>
#include "read_input.c"
#include "write_output.c"
#include "unistd.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

/*
Julio Hernandez 
88382550

Lab #1 Context Switch/Swap
The purpose of this lab is to replicate the behaviour of a context swap.
This will be achive by forking a process the using a pipe to time the time elapsed
from process to process.
*/


//global variable to keep track of time at all times
clock_t initialTime;
clock_t endingTime;

//global to keep track of the error margin at all times
double avgError;
double avgSwap;

//main program
int main() {

   //test string to for the program to read and write
   char* input = "Text written by the Parent\n";

   //initialized an array to hold each process
   int my_pipe[2];

   //statement to create pipe and in addition check if a pipe was successfully created
   if(pipe(my_pipe) < 0){
        printf("Pipe Failed!\n");
        return -1;
    }

    //fork initialized process has now be split into 2
   __pid_t p = fork();

   //variable created to test 100 trials
   int loops = 200;

   //loop for testing purposes to test context swap behaviour
   for(int i = 0; i<loops; i++){

      //precaution to check if fork failed (this is very rare)
      if(p<0){
         printf("Fork failed!\n");
         return -1;
      }

      //if statement to check if the current process is the parent
      if(p>0){
         //block the other process
         close(my_pipe[0]);
         //user function to write string
         //write_output(input);
         close(my_pipe[1]);
         //clocks are measured to check the error margin
         clock_t errorTime = clock();
         clock_t errorElapsedTime = clock();
         //error is summed
         avgError += ((errorElapsedTime-errorTime)/(double)CLOCKS_PER_SEC);
         //the timer for the context switch has been initiated 
         initialTime = clock();
         //wait for the next process
         wait(NULL);
      }

      //child process
      else{
         //record the time for the contect switch
         endingTime = clock();
         //add the time to the holder variable
         avgSwap += (endingTime-initialTime)/(double)CLOCKS_PER_SEC;
         printf("Context Swap Time: %.9lf ms\n", ((endingTime-initialTime)/(double)CLOCKS_PER_SEC));
         //block process
         close(my_pipe[1]);
         //read string
         write_output(input);
         close(my_pipe[0]);
      }
   }

   //print message depending on which process is being run after the loops have concluded
   if(p==0){
   printf("Context Swap Average Time: %.9lf ms\n", (avgSwap/loops));
   }
   else{
      printf("Something Else\n");
   }

   return 0;
}//emd of program
