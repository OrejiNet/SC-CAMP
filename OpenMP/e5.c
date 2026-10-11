#include <stdlib.h>
#include <stdio.h>

#define MAX 1000
int N=MAX;
double arrayA[MAX];
double arrayB[MAX];

double product(double* a, double* b, int N) 
{ int i=0;
  double sum = 0.0;
#pragma omp parallel for shared(sum)
   for(i=0; i<N; i++) {
#pragma omp critical
   sum += a[i] * b[i];
   }
  return sum;
}

int main()
{ int i=0;
  double f=0.0; 
  for (i=0;i<N;i++)
      { arrayA[i]=  i;
        arrayB[i]=2*i;
      }
  f=product(arrayA,arrayB,N);
  printf(" result: %f\n",f);  
exit (0);
}
