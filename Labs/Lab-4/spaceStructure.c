#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "spaceStructure.h"

int *ptr = initialStorage;
int startLooking = 0;
int roundIndex = 0;
int internalRoundIndex = 0;
int internalFragm = 0;

void init(int *p){
    int i;

    for(i = 0; i < HEAPSIZE; i++)
        *(p+i) = -1;
}

int pow2(int initial){
    int powerOf2 = 1, power = 1;
    while(powerOf2 < initial){
        power *= 2;
        powerOf2 = 2 * power;
    }

    return powerOf2;
}

char enoughSpace(int start, int end, int heap[]){
    if((start + end) > HEAPSIZE)
        return 1;

    int i;
    for(i = start; i < (start+end); i+=16){
        if(heap[i] != -1)
            return 1;
    }

    return 0;
}

int findEnd(int start, int heap[]){
    int i, end = start;
    for(i = start; i < HEAPSIZE; i++){
        if(heap[i] == -1)
            end++;
        else
            break;        
    }

    return end;
}

//If you uncomment the 2 lines inside, it will print ALL the indeces that are available
void totalExternalFragmentation(int *heap){
    int i, total = 0;
    for(i = 0; i < HEAPSIZE; i+=16){
        if(*(heap+i) == -1){
            //printf("At index: ");
            //convertToHex(i);
            total+= 16;
        }
    }

    printf("Total External Fragmentation: %d\n", total);
}

void printHeap(int *h){
    int i;
    for(i = 0; i < HEAPSIZE; i++){
        if(i % 16 == 0)
            printf("%d\n", *(h+i));
    }
}

void setArray(int *a){
    int i;
    for(i = 0; i < 10; i++)
        *(a+i) = 0;
}

void readNums(int *p, char* title){
    int counter = 0;
    char str[HEAPSIZE];
    FILE *in_file = fopen(title, "r");
    if(!in_file){
        printf("Oops, file can't be read\n");
        exit(-1);
    }

    while(fgets(str, HEAPSIZE, in_file) != NULL){
        int in_num = atoi(str);
        *(p+counter) = in_num;
        counter++;
    }
}

//From: https://www.quora.com/How-can-I-convert-from-decimal-to-hexadecimal-in-C-language
void convertToHex(int n){
    int decimal, quotient, remainder;
    int i, j = 0;
    char hexadecimal[100];
 
    quotient = n;
 
    while (quotient != 0){
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimal[j++] = 48 + remainder;
        else
            hexadecimal[j++] = 55 + remainder;
        quotient = quotient / 16;
    }
 
    for (i = j; i >= 0; i--)
        printf("%c", hexadecimal[i]);
    printf("\n");
}

void populateArray(int *in, int *a){
    int i = 0;
    while(i < 10){
        *(a+i) = *(in+roundIndex);
        roundIndex = (roundIndex+1) % NUMS;
        i++;
    }
}

//when given an index that we want to deallocate
void my_free(int process){
    int i;
    for(i = 0; i < HEAPSIZE; i++){
        if(*(ptr+i) == process)
            *(ptr+i) = -1;
    }
}
