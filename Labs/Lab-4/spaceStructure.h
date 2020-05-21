#ifndef STRUCTURE
#define STRUCTURE

#define HEAPSIZE 1048576
#define OPTIONS HEAPSIZE / 16
#define MAX 10000000
#define NUMS 1000

int initialStorage[HEAPSIZE];
int *ptr;
int startLooking;
int roundIndex; //Index that will rover around the totalNumbers list and won't stop
int internalRoundIndex; //Index that will go from 0 to 9 and go back to 0
int internalFragm;

typedef struct allocationChoice{
    char occupied;
    int startIndex;
    int endIndex;
    int fragmentation;
} Choice;

char enoughSpace(int, int, int[]);

int pow2(int);
int findEnd(int, int []);

void init(int *);
void my_free(int);
void setArray(int *);
void printHeap(int *);
void convertToHex(int);
void readNums(int *, char*);
void populateArray(int *, int *);
void totalExternalFragmentation(int *);

#endif
