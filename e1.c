#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

int main (int argc, char *argv[])
{ char machine_name[MPI_MAX_PROCESSOR_NAME];
  int MyId, N, namelenght;

  // BEGIN MPI OPERATIONS
  MPI_Init (&argc, &argv);
  
  //////////////////////////////////////////////////////////
  // MyId is the numbner in EACH processor. It is different for each node.
  // N is the total number of nodes. Is the same for everybody
  MPI_Comm_rank (MPI_COMM_WORLD, &MyId); 
  MPI_Comm_size (MPI_COMM_WORLD, &N);
  MPI_Get_processor_name(machine_name,&namelenght); 
  printf("Hi, I am process %d, from %d. I am in %s\n",MyId,N,machine_name); 
  
  // FINALIZE MPI OPERATIONS
  MPI_Finalize();
  exit(0);
}
