#include "write_output.h"
#include <stdio.h>
#include <stdlib.h>

void write_output(char out[])
{
    fprintf(stdout, out);
    printf("\n");
    fflush(stdout);
}
