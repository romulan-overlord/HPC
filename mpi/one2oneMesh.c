// 9. Implement One-to-all Broadcast in a Mesh (for p which is a perfect square).

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>  
#include<mpi.h>

//start with process 0 broadcast to all

void linearOneToAllBCast(int *data, int rank, int dim, int axis){
	int i = 0;
	MPI_Status status;
	for(i = 1; i < dim; i *= 2){
	    if(rank >= i && rank < i*2){
	      // printf("%d receiving from %d\n", rank, rank-i);
	      MPI_Recv(data, 1, MPI_INT, rank-i,1, MPI_COMM_WORLD, &status);
	    }
	    if(rank < i && (rank + i) < dim){
	      // printf("%d sending to %d\n", rank, rank+i);
	      MPI_Send(data, 1, MPI_INT, rank + i , 1, MPI_COMM_WORLD);
	    }
	}
}

void rowCast(int *data, int rank, int dim){
	int i = 0;
	MPI_Status status;
	for(i = 1; i < dim; i *= 2){
		if(rank >= dim * i && rank < i * 2 * dim){
			// printf("%d receiving from %d\n", rank, rank-i*dim);
			MPI_Recv(data, 1, MPI_INT, rank- i * dim,1, MPI_COMM_WORLD, &status);
		}
		if(rank < dim * i && rank + dim * i < dim * dim){
			// printf("%d sending to %d\n", rank, rank+i * dim);
			MPI_Send(data, 1, MPI_INT, rank + dim * i , 1, MPI_COMM_WORLD);
		}
	}
}

void rowToRowBCast(int *data, int rank, int size){
	int dim = (int)sqrt((double)size);
	int i = 0;
	//perform a one to broadcast in the x axis.
	linearOneToAllBCast(data, rank, dim, 0);
	printf("interval: %d has %d\n", rank, *data);
	sleep(3);
	//each column performs a one to all broadcast along the y axis
	rowCast(data, rank, dim);
}

int main( int argc, char **argv){
	int rank, size, i = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int data = rank == 0 ? 99 : 0;
	rowToRowBCast(&data, rank, size);

	printf("%d has %d\n", rank, data);
	MPI_Finalize();	
}