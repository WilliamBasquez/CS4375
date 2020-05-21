#include <stdio.h>
#include <stdlib.h>
#include "spaceStructure.h"
char bestFit(int process, int requestedSize, int heap[]){
    int i = 0, bestIndex = -1, counter = 0, diff = MAX;
    int blocks = pow2(requestedSize);
    Choice option;
    Choice listChoices[OPTIONS];

    while(i < HEAPSIZE){
        if(enoughSpace(i, blocks, heap) == 0){ //there's enough space, add this block as an option
            option.occupied = 0; // 0 = yes
            option.startIndex = i;
            option.endIndex = (i + blocks);
            option.fragmentation = findEnd(i, heap) - option.startIndex;
            listChoices[counter] = option;
            counter++;
            i = findEnd(option.startIndex, heap);
        } else
            i += 16;
    }

    for(i = 0; i < counter; i++){
        if(listChoices[i].occupied != 0){ //!0 = available
            printf("Allocation failed 1: %d\n", requestedSize);
            return -1;
        }
    }

    for(i = 0; i < counter; i++){
        if(listChoices[i].fragmentation < diff){
            bestIndex = listChoices[i].startIndex;
            diff = listChoices[i].fragmentation;
        }
    }

    if(bestIndex == -1){
        printf("Allocation failed 1: %d\n", requestedSize);
        return -1;
    }

    for(i = bestIndex; i < (bestIndex + blocks); i++)
        heap[i] = process;

    return bestIndex;
}
