#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<mpi.h>

void compare_exchange_min(int my_id, int partner, int *data){
	int buffer = 0;
	MPI_Status status;
	MPI_Send(data, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
	if(buffer < *data)
		*data = buffer;
}

void compare_exchange_max(int my_id, int partner, int *data){
	int buffer = 0;
	MPI_Status status;
	MPI_Send(data, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
	if(buffer > *data)
		*data = buffer;
}

void bitonicSort(int p, int my_id, int *num){
	int d = (int)log2(p);
	int i = 0, j = 0, partner = 0, bit1 = 0, bit2 = 0;
	for(i = 0; i < d; i++){
		for(j = i; j >= 0; j--){
			partner = my_id ^ (int)pow(2,j);
			bit1 = my_id & (int)pow(2,j);
			bit2 = my_id & (int)pow(2,i+1);
			if( (bit1 == 0 && bit2 == 0) || (bit1 > 0 && bit2 > 0)){
				// printf("compare exchange min between %d and %d, my value = %d while i = %d and j = %d\n", my_id, partner, *num, i, j);
				compare_exchange_min(my_id, partner, num);
			} else {
				// printf("compare exchange max between %d and %d, my value = %d while i = %d and j = %d\n", my_id, partner, *num, i, j);
				compare_exchange_max(my_id, partner, num);
			}
		}
	}
}

int main(int argc, char **argv){
	int rank = 0, size = 0, data = 0, org = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand(rank);

	data = rand() % 1000;
	org = data;

	bitonicSort(size, rank, &data);
	sleep(rank);

	printf("I am % d with %d previously %d\n", rank, data, org);

	// int a = 1, b = 1;
	// printf("%d   %d\n",a & 1, a & 2);

	MPI_Finalize();

}