#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<omp.h>

void display2D(double **arr, int N)
{
	printf("printing 2d: \n");
	int i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			printf("%lf  ", arr[i][j]);
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

void display1DINT(int *arr, int N)
{
	printf("printing 1d: \n");
	int i = 0;
	for(i = 0; i<N; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n\n");
}

void swap(int *x,int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main()
{
	int i=0, j=0, N = 20000, x, y, start, end;
	double **arr = (double **)malloc(N*sizeof(double*));
	for(i = 0; i < N; i++){
		arr[i] = (double*)malloc(N*sizeof(double));
	}
	double *vector = (double *)malloc(N*sizeof(double));
	double *output = (double *)malloc(N*sizeof(double));
	int *map = (int *)malloc(N*sizeof(int));

	for(i = 0; i < N; i++){
		map[i] = i;
	}

	// printf("original map: \n");
	// display1DINT(map, N);

	//create random mapping for load balancing
	start = omp_get_wtime();
	// sleep(5);
	for(int i = 0; i < N; i++){
		srand(i);
		x = rand() % N;
		y = rand() % N;
		swap(map + x, map + y);
	}
	end = omp_get_wtime();

	printf("delay: %d", end - start);

	// printf("perma map: \n");
	// display1DINT(map, N);

	// allocating values to array and vector
	#pragma omp parallel for schedule(dynamic, 8000) collapse(2)
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			arr[map[i]][map[j]]= map[i]*map[j];
		}
	}

	// display2D(arr,N);

	#pragma omp parallel for schedule(dynamic, 8000)
	for(i=0; i < N; i++){
		vector[map[i]] = map[i];
		output[i] = 0;
	}

	// display1D(vector, N);

	// doing vector multiplication
	#pragma omp parallel for collapse(2) schedule(dynamic, 8000)
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			output[(map[i])] += arr[(map[i])][(map[j])] * vector[(map[j])];
		}
	}

	// display1D(vector, N);

	// display2D(arr, N);

	printf("Output vector: \n");
	// display1D(output, N);

	free(output);
	free(vector);
	for(i = 0; i < N; i++){
		free(arr[i]);
	}
	free(arr);
}	
