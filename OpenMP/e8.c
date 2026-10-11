#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int i;
int node,numnodes;

int main ( int argc, char **argv) {                                  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &node);
  MPI_Comm_size(MPI_COMM_WORLD, &numnodes);
  omp_set_num_threads(3);

#pragma omp parallel
  printf(" I am thread %d of %d threads inside process %d of %d \
          processors\n",omp_get_thread_num(),omp_get_num_threads(),
          node,numnodes);

  MPI_Finalize();
}
