#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank= 0, size= 0, i = 0, j = 0, a=0;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  status.MPI_TAG = -1;

  if(rank == 0){
    status.MPI_TAG = 0;
    a = 100;
  }

  for(i = 1; i < size; i *= 2){
    if(rank >= i && rank < i*2){
      // printf("%d receiving from %d\n", rank, rank-i);
      MPI_Recv(&a, 1, MPI_INT, rank-i,1, MPI_COMM_WORLD, &status);
    }
    if(rank < i && (rank + i) < size){
      // printf("%d sending to %d\n", rank, rank+i);
      MPI_Send(&a, 1, MPI_INT, rank + i , 1, MPI_COMM_WORLD);
    }
  }

  // while(i < size){
  //   if(rank >= i && rank < i*2){
  //     // printf("%d receiving from %d\n", rank, rank-i);
  //     MPI_Recv(&a, 1, MPI_INT, rank-i,1, MPI_COMM_WORLD, &status);
  //   }
  //   if((rank + i) < size && rank < i){
  //     printf("%d sending to %d\n", rank, rank+i);
  //     MPI_Send(&a, 1, MPI_INT, rank + i , 1, MPI_COMM_WORLD);
  //   }
  // }

  // for(j = 0; j < i; j++){
  //   if(status.MPI_TAG == -1){
  //     printf("%d receiving from %d\n", rank, rank-i);
  //     MPI_Recv(&a, 1, MPI_INT, rank-j,1, MPI_COMM_WORLD, &status);
  //   }
  //   if(rank == j){
  //     printf("%d sending to %d\n", rank, rank+i);
  //     MPI_Send(&a, 1, MPI_INT, rank + j , 1, MPI_COMM_WORLD);
  //   }
  // }


  printf("%d got %d\n",rank,a);
  MPI_Finalize();
}