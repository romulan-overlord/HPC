#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

void All2AllBcast(int my_id, int p, int msg, int *result){
	MPI_Status status;
	int dim = (int)sqrt(p);
	int row = my_id / dim;
	int col = my_id % dim;
	int l = (row * dim )+ ((col - 1 + dim) % dim);
	int r = row * dim  + ((col + 1) % dim);
	int tracker = my_id, i = 0;
	int * recvBuffer = (int*)malloc(dim * sizeof(int));
	result[tracker] = msg;
	tracker = (row * dim) + ((tracker + 1) % dim);
	for(i = 1; i <= dim - 1; i++){
		// printf("i am %d sending to %d\n", my_id, l);
		MPI_Send(&msg, 1, MPI_INT, l, 1, MPI_COMM_WORLD);
		// printf("i am %d receiving from %d\n", my_id, r);
		MPI_Recv(&msg, 1, MPI_INT, r, 1, MPI_COMM_WORLD, &status);
		result[tracker] = msg;
		tracker = (row * dim) + ((tracker + 1) % dim);
	}
	// for(i = 0; i < dim; i++){
	// 	printf("i am %d with %d at %d\n", my_id, result[i], i);
	// }
	int u = ((row + 1) % dim) * dim + col;
	int d = ((row - 1 + dim) % dim) * dim + col;
	for(i = 0; i < dim; i++ )
		recvBuffer[i] = result[i];
	for(i = 1; i <= dim - 1; i++){
		tracker = ((row - i + dim) % dim) * dim;
		printf("i am %d sending %d, %d, %d to %d\n", my_id, recvBuffer[0], recvBuffer[1], recvBuffer[2], u);
		MPI_Send(recvBuffer, dim, MPI_INT, u, 1, MPI_COMM_WORLD);
		MPI_Recv(recvBuffer, dim, MPI_INT, d, 1, MPI_COMM_WORLD, &status);
		printf("i am %d receiving %d, %d, %d from %d\n", my_id, recvBuffer[0], recvBuffer[1], recvBuffer[2], d);
		for(int j = 0; j < dim; j++ )
			result[tracker++] = recvBuffer[j];
	}
}

int main(int argc, char **argv){
	int rank = 0, size = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int * result = (int*)malloc(size * sizeof(int));

	All2AllBcast(rank, size, rank, result);

	for(int i = 0; i < size; i++){
		printf("i am %d with %d at %d\n", rank, result[i], i);
	}

	MPI_Finalize();
}