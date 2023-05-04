// 5. Write a simple MPI application to check if non-blocking MPI point-to-point calls are buffered or not.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<mpi.h>

int main(int argc, char **argv){
	int rank = 0, size = 0;
	MPI_Status status;
	MPI_Request request;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int data = 0;

	if(rank == 0){
		data = 99;
		sleep(3);
		MPI_Isend(&data, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);
		printf("sent %d: \n", data);

		data = 222;
		printf("updated data: %d\n", data);
	}
	else {
		// sleep(3);
		MPI_Irecv(&data, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);		//non blocking receive
		MPI_Wait(&request, MPI_STATUS_IGNORE);								//manually block the code from proceeding till recv is completed
		printf("Received data: %d\n", data);
	}
	MPI_Finalize();
}

//conclusion: it is buffered.