#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank= 0, size= 0, a= 0, b= 0;
  MPI_Status status;
  MPI_Request r= MPI_REQUEST_NULL;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank == 0){
    a= 100;
    b= 200;
    MPI_Send(&a,1,MPI_INT,1,9,MPI_COMM_WORLD);
    MPI_Send(&b,1,MPI_INT,1,99,MPI_COMM_WORLD);
  }
  else{
    MPI_Recv(&b,1,MPI_INT,0,9,MPI_COMM_WORLD,&status);
    MPI_Recv(&a,1,MPI_INT,0,9,MPI_COMM_WORLD,&status);
  }

  printf("%d got %d %d\n",rank,a,b);
  MPI_Finalize();
}
