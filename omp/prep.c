//matrix matrix mul, i guess

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void display2D(long **arr, int N)
{
	printf("printing 2d: \n");
	int i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			printf("%ld  ", arr[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int N = 1000, i = 0, j = 0, k;
	long **mat1 = (long **)malloc(N * sizeof(long *));
	long **mat2 = (long **)malloc(N * sizeof(long *));
	long **result = (long **)malloc(N * sizeof(long *));

	#pragma omp parallel for schedule(dynamic, 8000)
	for(i = 0; i < N; i++){
		mat1[i] = (long *)malloc(N * sizeof(long));
		mat2[i] = (long *)malloc(N * sizeof(long));
		result[i] = (long *)malloc(N * sizeof(long));
	}

	#pragma omp parallel for schedule(dynamic, 8000) collapse(2)
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			mat1[i][j] = i * j;
			mat2[i][j] = i * j * 4;
			result[i][j] = 0;
		}
	}

	#pragma omp parallel for schedule(dynamic, 8000) collapse(3)
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			for(k = 0; k < N; k++){
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	printf("Output: \n");
	// display2D(result, N);

}

//old = 20s