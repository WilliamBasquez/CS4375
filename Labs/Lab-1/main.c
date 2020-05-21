//William Basquez
//CS 4375
//MW 3:00PM - 4:20PM
//Further explanations from: https://www.geeksforgeeks.org/pipe-system-call/
//                           https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*Calculating time with the function 'clock_t', but these are global, to remove any chance of them restarting or getting fuzzy results*/
clock_t start, end;
double switchTime;

int main() {
    int pipes[2];

    /*Default string to not input new ones each iteration*/
    char input[] = "My pipes are primo, Champ!\n";

   //Check if pipes were created successfully
    if(pipe(pipes) < 0){
        printf("Pipe Failed!\n");
        return -1;
    }

    //fork to split process into two
    int p = fork();

    //This variable will be used to compute the average context swap time
    int rounds;

   //loop to get a more generalized swap time
    for(rounds = 0; rounds < 20; rounds++){
        if(p < 0){
            printf("Fork failed!\n");
            return -1;
        }

        else if(p > 0){ //Parent process is running
            close(pipes[0]);
            write(pipes[1], input, 100);
            close(pipes[1]);

            //Start time
            start = clock();
            wait(NULL);
        } else{ //Child process is running
            //End of swap task
            end = clock();
         
            //Now, to get a better approx. time, each iteration we add the time it took to swap between process A to B, and vice versa
            switchTime += (end - start)/(double)CLOCKS_PER_SEC;
            
            //printf("Time it took to read/write string for this iteration: %.10lf ms\n", ((end - start)/(double)CLOCKS_PER_SEC));
            close(pipes[1]);
            read(pipes[0], input, 100);
            close(pipes[0]);
        }
    }

   //Once the child process is running, it means a "done" process (in terms of swapping information)
    if(p==0){
        printf("Avg. Time: %.10lf ms\n", (switchTime/rounds));
        exit(0);
    }
   return 0;
}
