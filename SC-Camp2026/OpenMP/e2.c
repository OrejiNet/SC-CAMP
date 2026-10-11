#include <stdlib.h>
#include <stdio.h>

int main(char **argv,int argc)
{ int privateX=0;  
#pragma omp parallel
{ int sharedX=0;
  privateX++;
  sharedX++;
  printf("privateX %d sharedX %d\n",
         privateX,sharedX);
}
exit (0);
}
