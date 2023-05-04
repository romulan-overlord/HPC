#include<stdio.h>
#include<math.h>
#include<mpi.h>


void One2AllBCast(int my_id, int d, int *message, int src){
	int dst, source;
	MPI_Status status;
	int mask = (pow(2,d)) - 1;
	// printf("%d is mask\n", mask);
	for( int i = d-1; i >= 0; i--){
		mask = mask ^ (int)pow(2,i);
		// printf("%d is new mask for %d\n", mask, my_id);
		if((my_id & mask) == 0){
			// printf("%d passed first if at mask = %d\n", my_id, mask);
			if((my_id & (int)pow(2,i)) == 0){
				dst = my_id ^ (int)pow(2,i);
				// printf("i am %d sending to %d\n", my_id, dst);
				MPI_Send(message, 1, MPI_INT, dst, 1, MPI_COMM_WORLD);
			} else {
				source = my_id ^ (int)pow(2,i);
				// printf("i am %d receiving from %d\n", my_id, source);
				MPI_Recv(message, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
			}
		}
	}
}

int main(int argc, char **argv){
	int rank = 0, size = 0, message = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0){
		message = 99;
	}

	One2AllBCast(rank, 3, &message, 0);

	printf("i am %d and i have %d\n", rank, message);

	MPI_Finalize();
}