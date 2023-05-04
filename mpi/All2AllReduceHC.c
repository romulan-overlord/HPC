#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

void All2ALlReduce(int my_id, int* msg, int d, int * result){
	MPI_Status status;
	int mask = 0, partner = 0, sendOff = 0, rcvOff = 0;
	for(int i = d-1; i >=0; i--){
		int *temp = (int *)malloc((int)pow(2,i) * sizeof(int));
		mask = (mask ^ (int)pow(2,i));
		partner = (my_id ^ (int)pow(2,i));
		sendOff = partner & mask;
		rcvOff = my_id & mask;
		// printf("i am %d sending to %d\n", my_id, partner);
		MPI_Send(msg + sendOff, ((int)pow(2,i)), MPI_INT, partner, 1, MPI_COMM_WORLD);
		MPI_Recv(temp, ((int)pow(2,i)), MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
		// printf("i am %d receiving from %d\n", my_id, partner);
		for(int j = 0; j < (int)pow(2,i); j++){
			msg[rcvOff + j] += temp[j];
		}
	}
	*result = msg[my_id];
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

	All2ALlReduce(rank, msg, (int)log2(size), &result);
	printf("i am %d with %d\n", rank, result);

	MPI_Finalize();
}