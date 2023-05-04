#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank= 0, size= 0, a= 0, b= 0, i= 0;
  MPI_Status status;
  MPI_Request r= MPI_REQUEST_NULL;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank > 0)
    MPI_Recv(&a,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
  if(rank == 0){
    sleep(5);
    a= 100;
  }
  if(rank < size-1)
    MPI_Send(&a,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);

  printf("%d got %d\n",rank,a);
  MPI_Finalize();
}
