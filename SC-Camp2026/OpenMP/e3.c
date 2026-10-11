#include <stdlib.h>
#include <stdio.h>

int main(char **argv,int argc)
{ int i=0; 
#pragma omp parallel for
     for (i=0;i<1000;i++)
         printf("%d \n",i);
exit (0);
}
