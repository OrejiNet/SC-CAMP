#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define lim 20

// SOURCE OF DATA TO BE PROCESSED
int buf[lim]= {27,24,3,8,45,10,50,15,10,11,9,48,69,25,19,29,61,72,93,20};
  
int buf2[lim]; 
int buf3[lim];
int max;

int main(int argc, char *argv[])
{
    int  n, myid, numprocs, i;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
//if (My_id==MAStER) read(buff);
  // BEGIN MPI OPERATIONS
  MPI_Init(&argc,&argv);

  //////////////////////////////////////////////////////////
  // myid is the numbner in EACH processor. It is different for each node.
  // numprocs is the total number of nodes. Is the same for everybody
  //////////////////////////////////////////////////////////
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  MPI_Get_processor_name(processor_name,&namelen);
  fprintf(stderr,"Process %d in %s\n",myid, processor_name);

  // n IS THE SIZE OF CHUNK TO BE SENT TO NODES
  n=lim/numprocs;
  
  // MPI_ScatterDIVIDES buf AND PUTS n ELEMENTS IN buf2. NODE 0 IS SOURCE AND SEND (INCLUDIGN ITSELF), EVERYONE ELSE RECEIVES
  // EXAMPLE: SUPPOSE ARRAY HAS [10,2,3,12,5,6,7,8,9,1,11,4] AND THERE ARE 4 NODES
  // n=3
  // AFTER SCATTER:
  // NODE 0's buff2 : [10,2,3]
  // NODE 1's buff2 : [12,5,6]
  // NODE 2's buff2 : [7,8,9]
  // NODE 3's buff2 : [1,11,4]
  MPI_Scatter(buf,n, MPI_INT,buf2,n,MPI_INT, 0, MPI_COMM_WORLD);

  // SHOWS WHAT EACH NODE RECEIVED FROM NODE 0  
  for (i=0; i<n ; i++)
	  printf("%d,Buf2[%d]= %d \n",myid, i,buf2[i]);
    
  // MPI_Reduce APPLIES THE OPERATION OVER buff2 (IN THIS CASE, MPI_MAX)
  //   AND SETS RESULT ON buf3. NOTE THAT EVERY NODE SENDS n ELEMENTS TO NODE 0
  // NODE 0 RECEIVES n ELEMENTS FROM numprocs NODES(INCLUDING ITLSEF) ON buf3
  // REDUCES APPLIES THE MPI_INT OPERATION OVER THE numprocs MESSAGES AND STORES IN buf3
  // THE RESULTS
  // FOR THE SAME EXAMPLE ABOVE, ON NODE 0
  // buf3 THEN IS [12,11,9] i.e. THE MAXIMUM FOR EACH PLACE SINCE
  // MAX(10,12,7,1) = 12
  // MAX(2,5,8,11) = 11
  // MAX(3,6,9,4) = 9
  MPI_Reduce(buf2,buf3,n, MPI_INT, MPI_MAX, 0,MPI_COMM_WORLD);
    
  // ONLY THE MASTER EXECUTES THE LAST SEARCH	
  if (myid == 0)
	{ max = buf3[0];
	  for (i=1; i<n ; i++)
       	  if (max < buf3[i])  max = buf3[i];
      for (i=0; i<n ; i++)
	      printf("Buf3[%d]= %d \n", i, buf3[i]);
      printf("Maximum element on array is :  %d \n", max);
	}
  
  // FINALIZE MPI OPERATIONS
  MPI_Finalize();
  return 0;
}

