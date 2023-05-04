#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

void AllReduce(int my_id, int p, int msg, int *result){
	MPI_Status status;
	int d = (int)log2(p);
	int tracker = 0;
	*result = msg;
	int *recvBuffer = (int*)malloc((int)pow(2,d-1) * sizeof(int));
	int *temp = (int*)malloc(p * sizeof(int));
	temp[tracker++] = msg;

	recvBuffer[0] = msg;

	for(int i = d-1; i >= 0; i--){
		// printf("i am %d sending %d units to %d\n", my_id, (int)pow(2,d-i-1), (my_id ^ (int)pow(2,i)));
		MPI_Send(temp, (int)pow(2,d-i-1), MPI_INT, (my_id ^ (int)pow(2,i)), 1, MPI_COMM_WORLD);
		MPI_Recv(recvBuffer, (int)pow(2,d-i-1), MPI_INT, (my_id ^ (int)pow(2,i)), 1, MPI_COMM_WORLD, &status);
		// printf("i am %d receiving %d units from %d\n", my_id, (int)pow(2,d-i-1), (my_id ^ (int)pow(2,i)));
		for(int j = 0; j < (int)pow(2,d-i-1); j++){
			temp[tracker++] = recvBuffer[j];
			*result += recvBuffer[j];
		}
			// printf("i am %d receiving %d from %d\n", my_id, recvBuffer[j], (my_id ^ (int)pow(2,i)));
	}

}

int main(int argc, char **argv){
	int rank = 0, size = 0, result = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int msg = rank;
	// int * result = (int*)malloc(size * sizeof(int));

	AllReduce(rank, msg, (int)log2(size), &result);
	printf("i am %d with %d\n", rank, result);

	MPI_Finalize();
}