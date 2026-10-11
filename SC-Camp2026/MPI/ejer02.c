#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#define LIM 10

int main (int argc, char *argv[]) {
  double first,last;
  int i,error, MyId, N;
  int buff[LIM]={10,20,30,40,50,60,70,80,90,100};
  MPI_Status status;
  MPI_Init (&argc, &argv);

  //////////////////////////////////////////////////////////
  // MyId is the numbner in EACH processor. It is different for each node.
  // N is the total number of nodes. Is the same for everybody
  //////////////////////////////////////////////////////////
  MPI_Comm_rank(MPI_COMM_WORLD, &MyId);
  MPI_Comm_size(MPI_COMM_WORLD, &N);
  
  //////////////////////////////////////////////////////////
  // THIS PROGRAM ONLY WORKS WITH TWO PROCESSORS
  //////////////////////////////////////////////////////////
  if (N != 2) {
    fprintf(stderr,"This program is only for two processors");
    MPI_Finalize();
    exit(1);
  }

  //////////////////////////////////////////////////////////
  // THIS PART OF CODE IS EXECUTED ONLY IN NODE 0 (MASTER)
  //////////////////////////////////////////////////////////
  if (MyId == 0)
  { 
    // Sends buff variable (LIM elements of size MPI_INT) to processor 1. TAG 111 is optional
    MPI_Send(buff, LIM, MPI_INT, 1, 111, MPI_COMM_WORLD);
	
	// Prints the array being sent
	printf("I am process %d, and sent:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
	
    // Receives LIM elements of size MPI_INT and stores it in variable buff. It receives FROM processor 1
	MPI_Recv(buff, LIM, MPI_INT, 1, 222, MPI_COMM_WORLD, &status);
    
	// Prints the array being received FROM slave node
	printf("I am process %d, and received:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");

  } 
  //////////////////////////////////////////////////////////
  // THIS PART OF CODE IS EXECUTED ONLY IN NODE 1 (SLAVE)
  //////////////////////////////////////////////////////////
  else
  {  
    // Receives LIM elements of size MPI_INT and stores it in variable buff. It receives FROM processor 0
    MPI_Recv(buff, LIM, MPI_INT, 0, 111, MPI_COMM_WORLD, &status);
    
	// Prints exactly what receives from node 0
	printf("I am process %d, and received:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
	
    // Processes the array buff. This process just adds 1 to each element on buff
	for (i=0;i<LIM;i++) 
      buff[i]+=MyId; 
    
	// Sends buff variable (LIM elements of size MPI_INT) to processor 0. TAG 111 is optional
    MPI_Send(buff, LIM, MPI_INT, 0, 222, MPI_COMM_WORLD);
	
	// Prints the information just sent TO node 0
    printf("I am process %d, and sent:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
   }

  // FINALIZE MPI OPERATIONS
  MPI_Finalize();
  exit(0);
}
