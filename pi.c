#include "stdio.h"
#include "stdlib.h"
#include "omp.h"

static long num_steps=1000000; 
double step, pi;

///////////////////////
// con num_steps en 1000000 la salida debe ser
// Pi = 3.14159265358976425020
////////////////////////

void main()
{  int i;
   double x, sum = 0.0;

   step = 1.0/(double) num_steps;
   for (i=0; i< num_steps; i++){
      x = (i+0.5)*step;
      sum = sum + 4.0/(1.0 + x*x);
   }
   pi = step * sum;
   printf("Pi = %.20lf\n",pi);
}
