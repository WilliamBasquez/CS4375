/* Program to demonstrate time taken by function fun() */
#include <stdio.h> 
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
  
// A function that terminates when enter key is pressed
void print(char string[], char start, char end)
{
    int diff = end - start;
    while(start < diff)
    {
        printf("%c", string[start]);
        start++;
    }
    printf("\n");
}

void fun(char in[])
{
    int index = 0;
    char start = 0, end = 0;

    while(index < strlen(in))
    {
        if(in[index] == '|')
        {
            end = index;
            print(in, start, end);
        } else
        {
            start = end;
        }
        index++;
    }
    print(in, start+1, index);
} 
  
// The main program calls fun() and measures time taken by fun() 
int main() 
{ 
    // Calculate the time taken by fun()
    char testArray[100] = "cat contents.txt | grep file | awk '{print $9}'";
    const char s[2] = "|";
    char *temp;
    printf("Here\n");

    temp = strtok(testArray, s);

    while(temp != NULL){
        printf("%s\n", temp);
        temp = strtok(NULL, s);
    }
}