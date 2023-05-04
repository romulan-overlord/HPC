#include<stdio.h>
#include<omp.h>
#include<unistd.h>

void display1D(int arr[10])
{
	printf("printing 1d: \n");
	int i = 0;
	for(i = 0; i<10; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n\n");
}

int custom(int in, int out){
	printf("in custom with %d and %d\n", in, out);
	printf("called in %d while %d live\n", omp_get_thread_num(), omp_get_num_threads());
	return (in + out);
}

int main()
{
	int size;
	int arr[10] = {};

	#pragma omp declare reduction(custom:int:omp_out=custom(omp_in, omp_out)) initializer(omp_priv = 0)

	#pragma omp parallel reduction(custom:arr[:10])
	{
		int rank = omp_get_thread_num();
		for(int i  = 0; i < 10; i++){
			arr[i] = rank * 2 + i;
		}
		printf("printing init array from %d:\n", rank);
		display1D(arr);
		if(rank == 0)
			sleep(3);

	}

	printf("printing output: \n");
	display1D(arr);

}