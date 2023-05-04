#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void display2D(int *arr, int N)
{
	printf("printing 2d: \n");
	int i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			printf("%d  ", *(arr + sizeof(int) * i + j));
		}
		printf("\n");
	}
}

void display1D(int *arr, int N)
{
	printf("printing 1d: \n");
	int i = 0;
	for(i = 0; i<N; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n\n");
}

int main()
{
	int i=0, j=0, N = 20000, upper = 10, lower = 0;
	int *arr = (int *)malloc(N*N*sizeof(int));
	int *vector = (int *)malloc(N*sizeof(int));
	int *output = (int *)malloc(N*sizeof(int));

	//allocating values to array and vector
	// #pragma omp parallel for collapse(2)
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			*(arr + sizeof(int) * j + i) = (rand() % 10);
		}
	}

	// #pragma omp parallel for 
	for(i=0; i < N; i++){
		vector[i] = (rand() % 10);
		output[i] = 0;
	}

	//doing vector multiplication
	// #pragma omp parallel for collapse(2)
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			output[j] += *(arr + sizeof(int) * j + i) * vector[i];
		}
	}

	// display1D(vector, N);

	// display2D(arr, N);

	printf("Output vector: \n");
	display1D(output, N);

	free(output);
	free(vector);
	free(arr);
}	
