#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int node, numnodes, provided;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Comm_size(MPI_COMM_WORLD, &numnodes);
    omp_set_num_threads((node+1)*2);

    #pragma omp parallel
    printf("I am thread %d of %d threads inside process %d of %d processors\n",
           omp_get_thread_num(), omp_get_num_threads(), node, numnodes);

    MPI_Finalize();
    return 0;
}
