#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void display2D(double *arr, int N)
{
	printf("printing 2d: \n");
	int i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			printf("%lf  ", *(arr + sizeof(double) * i + j));
		}
		printf("\n");
	}
}

void display1D(double *arr, int N)
{
	printf("printing 1d: \n");
	int i = 0;
	for(i = 0; i<N; i++){
		printf("%lf\t", arr[i]);
	}
	printf("\n\n");
}

int main()
{
	int i=0, j=0, N = 10, upper = 10, lower = 0;
	// double *arr = (double *)malloc(N*N*sizeof(double));
	double *vector = (double *)malloc(N*sizeof(double));
	// double *output = (double *)malloc(N*sizeof(double));

	double temp[20000] = {};

	// allocating values to array and vector
	#pragma omp parallel for
	for(i=0; i < N; i++){
		vector[i] = rand();
		// output[i] = 0;
		// temp[i] = 0;
	}

	display1D(vector, N);
}