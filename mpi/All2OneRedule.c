#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

int * All2OneReduce(int my_id, int p, int *arr, int len){
	int d = (int)log2(p);
	int mask = 0, dst, src;
	int *res = (int*)malloc(len * sizeof(int));
	MPI_Status status;

	for( int j = 0; j < len; j++)
		res[j] = arr[j];

	for(int i = 0; i < d; i++){
		if((my_id & mask) == 0){
			if((my_id & (int)pow(2,i)) != 0){
				dst = my_id ^ (int)pow(2,i);
				printf("i am %d sending to %d\n", my_id, dst);
				MPI_Send(arr, len, MPI_INT, dst, 1, MPI_COMM_WORLD);
			} else {
				src = my_id ^ (int)pow(2,i);
				printf("i am %d receiving from %d\n", my_id, src);
				MPI_Recv(arr, len, MPI_INT, src, 1, MPI_COMM_WORLD, &status);
				for(int j = 0; j < len; j++){
					res[j] += arr[j];
				}
			}
		}
		mask = mask ^ (int)pow(2,i);
	}
	return res;
}

//generalised source
int * All2OneReduceGeneral(int my_id, int p, int *arr, int len, int destination){
	int d = (int)log2(p);
	int mask = 0, dst, src;
	int v_id = my_id ^ destination;
	int *res = (int*)malloc(len * sizeof(int));
	MPI_Status status;

	for( int j = 0; j < len; j++)
		res[j] = arr[j];

	for(int i = 0; i < d; i++){
		if((v_id & mask) == 0){
			if((v_id & (int)pow(2,i)) != 0){
				dst = v_id ^ (int)pow(2,i);
				printf("i am %d sending to %d\n", my_id, (dst ^ destination));
				MPI_Send(arr, len, MPI_INT, (dst ^ destination), 1, MPI_COMM_WORLD);
			} else {
				src = v_id ^ (int)pow(2,i);
				printf("i am %d receiving from %d\n", my_id, (src ^ destination));
				MPI_Recv(arr, len, MPI_INT, (src ^ destination), 1, MPI_COMM_WORLD, &status);
				for(int j = 0; j < len; j++){
					res[j] += arr[j];
				}
			}
		}
		if(my_id == destination){
			for(int i = 0; i < len; i++)
				printf("%d\n", res[i]);
			printf("new dawn \n\n");
		}
		mask = mask ^ (int)pow(2,i);
	}
	return res;
}

int main(int argc, char **argv){
	int rank = 0, size = 0, len = 3, destination = 4;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int *arr = (int*)malloc(len * sizeof(int));
	for(int i = 0; i < len; i++){
		if(rank != destination)
			arr[i] = i + 1;
		else
			arr[i] = 0;
	}

	int * res = All2OneReduceGeneral(rank, 8, arr, len, destination);

	if(rank == destination){
		for(int i = 0; i < len; i++)
			printf("%d\n", res[i]);
	}

	MPI_Finalize();
}