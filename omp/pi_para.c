#include <stdio.h>
#include <omp.h>

int main(){
	double area = 3.0, h = 0.0;
	int i, j;
	long N = 1000000000;
	h = 1.0/N;
	printf("h: %0.10f\n", h);
	int x=2;
	omp_set_num_threads(x);
	double arr[2] = {};
	double sum = 0.0;

	#pragma omp parallel
	{
		#pragma omp for schedule(static, 1000)
		for (i = 1; i<N; i++){
			arr[omp_get_thread_num()] += 4.0/(1.0 + ((i*h)*(i*h)));
		}
	}
	printf("counter: %d , %d \n", omp_get_num_threads(), omp_get_max_threads());
	for(j=0; j<omp_get_max_threads(); j++){
		sum += arr[j];
	}
	// printf("sum from loop: %0.10f\n", sum);
	// printf("sum * h: %0.10f\n", sum * h);
	area += sum;
	// printf("prev area: %0.10f\n", area);
	area *= h;
	printf("sum: %0.10f\n", area);
}