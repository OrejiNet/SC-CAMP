#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#define LIM 10

int main (int argc, char *argv[]) {
  int i, MyId, N;
  int buff[LIM];
  MPI_Status status;
  MPI_Init (&argc, &argv);

  //////////////////////////////////////////////////////////
  // MyId is the rank of EACH process. It is different for each process.
  // N is the total number of processes. Is the same for everybody
  //////////////////////////////////////////////////////////
  MPI_Comm_rank(MPI_COMM_WORLD, &MyId);
  MPI_Comm_size(MPI_COMM_WORLD, &N);

  // Only the master (root) has the original data
  if (MyId == 0)
    for (i=0;i<LIM;i++)
      buff[i] = (i+1)*10;

  //////////////////////////////////////////////////////////
  // BROADCAST: EVERY process calls MPI_Bcast, not only the master.
  // In process 0 (root) it SENDS buff; in the rest it RECEIVES into buff.
  // No for loop, no tag, and no MPI_Recv needed in the slaves.
  //////////////////////////////////////////////////////////
  MPI_Bcast(buff, LIM, MPI_INT, 0, MPI_COMM_WORLD);

  //////////////////////////////////////////////////////////
  // THIS PART OF CODE IS EXECUTED ONLY IN PROCESS 0 (MASTER)
  //////////////////////////////////////////////////////////
  if (MyId == 0)
  {
    printf("I am process %d, and broadcast:\n", MyId);
    for (i=0;i<LIM;i++)
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");

    for(int p = 1; p <N; p++){
      // Receives LIM elements of size MPI_INT FROM process p
      MPI_Recv(buff, LIM, MPI_INT, p, 222, MPI_COMM_WORLD, &status);

      // Prints the array being received FROM slave process
      printf("I am process %d, and received from %d:\n", MyId, p);
      for (i=0;i<LIM;i++)
        printf("{%d,%d}",MyId,buff[i]);
      printf(" \n");
    }
  }
  //////////////////////////////////////////////////////////
  // THIS PART OF CODE IS EXECUTED IN ALL THE OTHER PROCESSES (SLAVES)
  //////////////////////////////////////////////////////////
  else
  {
    // buff already arrived through MPI_Bcast
    printf("I am process %d, and received:\n", MyId);
    for (i=0;i<LIM;i++)
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");

    // Processes the array buff. Adds its own rank to each element
    for (i=0;i<LIM;i++)
      buff[i]+=MyId;

    // Sends buff back to process 0 with tag 222
    MPI_Send(buff, LIM, MPI_INT, 0, 222, MPI_COMM_WORLD);

    // Prints the information just sent TO process 0
    printf("I am process %d, and sent:\n", MyId);
    for (i=0;i<LIM;i++)
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
  }

  // FINALIZE MPI OPERATIONS
  MPI_Finalize();
  exit(0);
}
