#include <stdlib.h>
#include <stdio.h>

#define start 100000001
#define end  1000000000
 
int testForPrime(long p)  //slow prime test 
{ long i=0;
  for(i=2; i<p; i++) {
      if ((p%i)==0) return 0;
   }
  return 1;
}

int main(char **argv,int argc)
{ long i=0;
  int gPrimesFound=0;
#pragma omp parallel for schedule (dynamic, 10)
  for (i = start; i <= end; i +=2)
     { if (testForPrime(i))
          gPrimesFound++;
     }
   printf("number of primes between %d and %d: %d\n",start,end,gPrimesFound);
}