#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int i;
int myid,numprocs;
int size=32;
int chunk=0;
int start=0;
int final=0;

int main(int argc,char **argv)
{ 

  // BEGIN MPI OPERATIONS
  MPI_Init(&argc,&argv);
  
  //////////////////////////////////////////////////////////
  // myid is the numbner in EACH processor. It is different for each node.
  // numprocs is the total number of nodes. Is the same for everybody
  //////////////////////////////////////////////////////////
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

  // SENDS THE VARIABLE size TO EVERYBODY. NODE 0 IS SENDER, EVERYONE ELSE RECEIVES
  MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // EACH NODE CALCULATES HOW MANY INDEXES HAS TO WORK
  chunk=size/numprocs;
  start=myid * chunk;
  final=start + chunk;
    
  // EACH NODE PRINTS OUT ITS INFORMATION
  printf(" I am node %d and I will work from %d to %d \n",myid,start,final);

  // NOTE THAT EACH NODE OF MPI UNIVERSE HAS ITS OWN THREADS FROM OPENMP UNIVERSE
  #pragma omp parallel for
  for (i=start;i<final;i++)
     { printf(" Thread %d, node %d process i=%d\n",omp_get_thread_num(),myid,i);  
     }

  // ENDS MPI OPERATIONS
  MPI_Finalize();
}


