#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank= 0, size= 0;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank != size-1)
    MPI_Send(&rank,1,MPI_INT,rank+1,1,MPI_COMM_WORLD);
  else
    MPI_Recv(&size,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);

  printf("%d got %d\n",rank,size);
  MPI_Finalize();
}
