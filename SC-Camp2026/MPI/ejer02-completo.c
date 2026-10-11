#include <stdio.h>
#include <mpi.h>
#define LIM 10
main (int argc, char *argv[]) {
  double inicio,final;
  int i,error, MyId, N;
  int buff[LIM]={10,20,30,40,50,60,70,80,90,100};
  MPI_Status status;
  MPI_Init (&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &MyId);
  MPI_Comm_size(MPI_COMM_WORLD, &N);
  if (N != 2) {
    fprintf(stderr,"Este programa solo funciona con dos (2) procesadores  ");
    MPI_Finalize();
    exit(1);
  }

  if (MyId == 0)
  { 
    inicio=MPI_Wtime();
    printf("Tiempo 1, Proceso 0: %lf\n",inicio);
    MPI_Send(buff, LIM, MPI_INT, 1, 111, MPI_COMM_WORLD);
    final=MPI_Wtime();
    printf("Tiempo 2, Proceso 0: %lf\n",final);
    printf("Soy el proceso %d, y envie:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
    inicio=MPI_Wtime();
    printf("Tiempo 3, Proceso 0: %lf\n",inicio);
    MPI_Recv(buff, LIM, MPI_INT, 1, 222, MPI_COMM_WORLD, &status);
    final=MPI_Wtime();
    printf("Tiempo 4,Proceso 0: %lf\n",final);
    printf("Soy el proceso %d, y recibi los mensajes:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");

  } else
    {  
    inicio=MPI_Wtime();
    printf("Tiempo 1,Proceso 1: %lf\n",inicio);
    MPI_Recv(buff, LIM, MPI_INT, 0, 111, MPI_COMM_WORLD, &status);
    final=MPI_Wtime();
    printf("Tiempo 2, Proceso 1: %lf\n",final);
    printf("Soy el proceso %d, y recibi:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
    for (i=0;i<LIM;i++) 
      buff[i]++; 
    inicio=MPI_Wtime();
    printf("Tiempo 3, proceso 1:%lf\n",inicio);
    MPI_Send(buff, LIM, MPI_INT, 0, 222, MPI_COMM_WORLD);
    final=MPI_Wtime();
    printf("Tiempo 4, proceso 1:%lf\n",final);
    printf("Soy el proceso %d, y envie:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    final=MPI_Wtime();
    printf(" \n");
    printf("Tiempo 5, proceso 1: %lf\n",final);
 }

  MPI_Finalize();
  exit(0);
}
