#include <stdio.h>
#include <stdlib.h>
#include "spaceStructure.h"
#include "best_fit.c"
#include "first_fit.c"
#include "next_fit.c"

int main(int argc, char *argv[]){
    init(ptr);
    int totalNumbers[NUMS], allocationList[10] = { };
    int *pointerToNums = totalNumbers;
    int *pointerToAlloc = allocationList;
    char *fileName = "random.txt";
    int times = 0, pass = 1, i, count;

    int j;
    if(argc == 1){
        printf("Enter 1 more number to determine which strategy to use:\n");
        printf("1) First Fit Algorithm\n2) Best Fit Algorithm\n3) Next Fit Algorithm\n");
        return 1;
    }
    else if (argc == 2){
        int selection = atoi(argv[1]);
        //storing all numbers in an array that will not change
        readNums(pointerToNums, fileName);

        //preparing 10 allocation locations, all elements are 0
        setArray(pointerToAlloc);

        if(selection == 1){
            printf("Testing Allocation with First Fit\n");
            while(1){
                populateArray(pointerToNums, pointerToAlloc);
                
                while(times < 10){
                    count = firstFit(times, allocationList[times], ptr);

                    if(count == -1){
                        printf("\nPass: %d\n", pass);
                        printf("Total internal Fragmentation: %d\n", internalFragm);
                        totalExternalFragmentation(ptr);
                        exit(-1);
                    }
                    times++;
                }
            pass++;

            for(i = 1; i < 10; i = i + 2)
                my_free(i);
            times = 0;
            setArray(pointerToAlloc);
            }
        }
        else if(selection == 2){
            printf("Testing Allocation with Best Fit\n");
            while(1){
                populateArray(pointerToNums, pointerToAlloc);
                
                while(times < 10){
                    count = bestFit(times, allocationList[times], ptr);

                    if(count == -1){
                        printf("\nPass: %d\n", pass);
                        printf("Total internal Fragmentation: %d\n", internalFragm);
                        totalExternalFragmentation(ptr);
                        exit(-1);
                    }
                    times++;
                }
                pass++;

                for(i = 1; i < 10; i = i + 2)
                    my_free(i);
                times = 0;
                setArray(pointerToAlloc);
            }
        }
        else if (selection == 3){
            printf("Testing Allocation with Next Fit\n");
            while(1){
                populateArray(pointerToNums, pointerToAlloc);
                
                while(times < 10){
                    count = nextFit(times, allocationList[times], ptr);

                    if(count == -1){
                        printf("\nPass: %d\n", pass);
                        printf("Total internal Fragmentation: %d\n", internalFragm);
                        totalExternalFragmentation(ptr);
                        exit(-1);
                    }
                    times++;
                }
                pass++;

                for(i = 1; i < 10; i = i + 2)
                    my_free(i);
                times = 0;
                setArray(pointerToAlloc);
            }
        }
        else{
            printf("Too many arguments (Only 1 is needed)\n");
            return 1;
        }    
    }

    return 0;
}