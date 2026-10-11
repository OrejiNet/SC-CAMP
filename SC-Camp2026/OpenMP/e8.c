 #include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int i;
int node,numnodes;

int main(char **argv,int argc)
{ MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&node);
  MPI_Comm_size(MPI_COMM_WORLD,&numnodes);

#pragma omp parallel
  printf(" I am thread %d of %d threads inside process %d of %d\   
          processors\n",omp_get_thread_num(),omp_get_num_threads(),node,numnodes);

  MPI_Finalize();
}
