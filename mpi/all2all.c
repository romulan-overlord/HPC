// 7. Let there be n processes. Let each process generate the ith row of a matrix (i = rank). Perform an MPI_Alltoall communication with these values. What does each process hold at the end of the communication?

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define N 10

int main( int argc, char **argv){
	int rank, size, i = 0;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int arr[N] = {};

	int data = rank;

	int receiver[N] = {};

	arr[rank] = rank;


	//sends data from a single variable, receive in an array indexed according to rank
	MPI_Alltoall(&data, 1, MPI_INT, receiver, 1, MPI_INT, MPI_COMM_WORLD);

	if(rank == 0)
		for(i = 0; i < N; i++){
			printf("%d\t", receiver[i]);
		}

	MPI_Finalize();
}