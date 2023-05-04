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

void Odd_Even_Sort(int p, int my_id, int *num){
	int i = 0, partner = 0;

	for(i = 0; i < p; i++){
		if(i % 2 == 0){
			if(my_id % 2 == 0 && my_id < p-1){
				partner = my_id +1;
				compare_exchange_min(my_id, partner, num);
			} else if (my_id % 2 == 1) {
				partner = my_id -1;
				compare_exchange_max(my_id, partner, num);
			}
		} else {
			if(my_id > 0){
				if(my_id % 2 == 1 && my_id < p-1){
					partner = my_id + 1;
					compare_exchange_min(my_id, partner, num);
				} else if(my_id % 2 == 0) {
					partner = my_id - 1;
					compare_exchange_max(my_id, partner, num);
				}
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

	data = rand() % 100;
	org = data;

	Odd_Even_Sort(size, rank, &data);
	sleep(rank);
	printf("I am % d with %d previously %d\n", rank, data, org);

	// int a = 1, b = 1;
	// printf("%d   %d\n",a & 1, a & 2);

	MPI_Finalize();

}