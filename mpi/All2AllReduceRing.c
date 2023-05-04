#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

void All2ALlReduce(int my_id, int* msg, int p, int * result){
	MPI_Status status;
	int l = (my_id -1 + p) % p;
	int r = (my_id +1) % p;
	int recv = 0, i = 0, j = 0;
	for(i = 1; i < p; i++){
		j = (my_id + i) % p;
		msg[j] += recv;
		MPI_Send(msg + j, 1, MPI_INT, l, 1, MPI_COMM_WORLD);
		MPI_Recv(&recv, 1, MPI_INT, r, 1, MPI_COMM_WORLD, &status);
	}
	*result = msg[my_id] + recv;
}

int main(int argc, char **argv){
	int rank = 0, size = 0, result = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int * msg = (int*)malloc(size * sizeof(int));

	for(int i = 0; i < size; i++){
		msg[i] = i;
	}

	All2ALlReduce(rank, msg, size, &result);
	printf("i am %d with %d\n", rank, result);

	MPI_Finalize();
}