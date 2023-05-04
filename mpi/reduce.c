#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char **argv){
	int rank = 0, size = 0, data = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	data = rand();
	int result = 0;

	printf("i am %d and my data before reduction is %d.\n", rank, data);

	MPI_Reduce(&data, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	//MPI_Reduce(send buffer, receive buffer(different from send buffer), count, datatype, operation, root, communicator)

	printf("i am %d and my result is %d.\n", rank, result);

	MPI_Finalize();
}