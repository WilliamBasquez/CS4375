#include <stdio.h>
#include <stdlib.h>
#include "spaceStructure.h"

int firstFit(int process, int requestedSize, int heap[]){
    int blocks = pow2(requestedSize);
    int i = 0, j;

    internalFragm += (blocks-requestedSize);

    while(i < HEAPSIZE){
        if(enoughSpace(i, blocks, heap) == 0){ //there's enough space, add this block as an option
            for(j = i; j < (i + blocks); j++)
                heap[j] = process;
            break;
        } else
            i += 16;
    }

    if(i == HEAPSIZE){
        printf("Allocation failed 1: %d\n", requestedSize);
        return -1;
    }

    return i;
}