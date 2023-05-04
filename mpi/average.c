// 4. Each rank, EXCEPT RANK 0, is to compute a set of k numbers. This k is random for each process. To simulate the process of generating k numbers, each process can use rand() k times to generate it and store it in an array of k integers. Rank 0 has to compute the average of all these numbers. At the end of their computation, each rank sends all its numbers to rank 0. Rank 0 will output the average of all the numbers as well as the order in which the other ranks completed their task.

#include <stdio.h>
#include<stdlib.h>
#include <mpi.h>

void display1D(int *arr, int N)
{
	printf("printing 1d: \n");
	// printf("N: %d and Arr: %p", N, arr);
	int i = 0;
	for(i = 0; i<N; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n\n");
}

int main(int argc, char **argv){
	int rank = 0, size = 0, k = 0, i = 0, j = 0, count = 0;
	long average = 0;
	int *arr = NULL;
	int **numArr = NULL;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int *sizeArr = NULL;
	srand(rank);

	// printf("help :%d\n", rank);

	if(rank != 0){
		k = rand() % 10000000;
		// printf("%d got k: %d\n",rank, k);
		//send size of array to be received
		MPI_Send(&k, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		arr = (int*)malloc(k * sizeof(int));
		for(i = 0; i < k; i++){
			arr[i] = rand();
		}
		// display1D(arr, k);
		MPI_Send(arr, k, MPI_INT, 0, 99, MPI_COMM_WORLD);
		free(arr);
	}
	else {
		// printf("stufff :%d\n", rank);
		numArr = (int **)malloc(size * sizeof(int*));
		sizeArr = (int*)malloc(size * sizeof(int));
		for(i = 1; i < size; i++){
			MPI_Recv(sizeArr + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			printf("%d received %d from %d\n", rank, sizeArr[i], i);
			numArr[i] = (int*)malloc(sizeArr[i] * sizeof(int));
			MPI_Recv(numArr[i], sizeArr[i], MPI_INT, i, 99, MPI_COMM_WORLD, &status);
			printf("%d received array from %d:\n", rank, i);
			// display1D(numArr[i], sizeArr[i]);
		}

		for(i=1; i<size; i++){
			for(j=0; j<sizeArr[i]; j++){
				// printf("averaging: %d\n", numArr[i][j]);
				average += numArr[i][j];
				count++;
			}
		}
		printf("sample: %d\n", numArr[1][456]);
		printf("sum = %ld\tcount = %d\n", average, count);
		average = average / count;
		printf("%d printing average: %ld\n", rank, average);
		for(i = 1; i < size; i++){
			free(numArr[i]);
		}
		free(numArr);
		free(sizeArr);
	}
	MPI_Finalize();
}