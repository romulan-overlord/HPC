#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

void All2AllBcast(int my_id, int p, int msg, int *result){
	MPI_Status status;
	int l = (my_id - 1 + p) % p;
	int r = (my_id + 1) % p;
	int tracker = my_id;
	result[tracker--] = msg;
	tracker = (tracker + p) % p;
	for(int i = 1; i <= p-1; i++){
		MPI_Send(&msg, 1, MPI_INT, r, 1, MPI_COMM_WORLD);
		MPI_Recv(&msg, 1, MPI_INT, l, 1, MPI_COMM_WORLD, &status);
		result[tracker--] = msg;
		tracker = (tracker + p) % p;
	}
}

int main(int argc, char **argv){
	int rank = 0, size = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int * result = (int*)malloc(size * sizeof(int));

	All2AllBcast(rank, 8, rank, result);

	for(int i = 0; i < size; i++){
		printf("i am %d with %d at %d\n", rank, result[i], i);
	}

	MPI_Finalize();
}