#include <stdio.h>
#include <stdlib.h>
#include "spaceStructure.h"

int nextFit(int process, int requestedSize, int heap[]){
    int counter = 0;
    startLooking = startLooking % HEAPSIZE;
    
    int blocks = pow2(requestedSize);
    int j, start = -1;

     while(counter < HEAPSIZE){
        if(enoughSpace(startLooking, blocks, heap) == 0){ //there's enough space, add this block as an option
            start = startLooking;
            for(j = start; j < (start + blocks); j++)
                heap[j] = process;
            break;
        } else
            startLooking = (startLooking + 16) % HEAPSIZE;
        counter += 16;
    }

    if(counter == HEAPSIZE){
        printf("Allocation failed 1: %d\n", requestedSize);
        return -1;
    }

    startLooking = j;
    return start;
}