#include <stdlib.h>
#include <stdio.h>

int main(char **argv,int argc)
{  
#pragma omp parallel
     printf("Hello world\n");
exit (0);
}
