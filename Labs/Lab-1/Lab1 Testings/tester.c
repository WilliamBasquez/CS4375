#include <stdio.h>
#include <stdlib.h>
#include "read_input.h"
#include "write_output.h"

int main()
{
    char in[50];
    printf("Enter a string: ");
    read_input(in);
    write_output(in);

    return 0;
}
