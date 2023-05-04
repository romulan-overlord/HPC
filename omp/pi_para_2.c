#include <stdio.h>
#include <omp.h>

int main(){
	double area = 3.0, h = 0.0;
	long N = 1000000000;
	h = 1.0/N;
	omp_set_num_threads(2);
	double sum = 0.0;

	#pragma omp parallel private(sum)
	{
		#pragma omp for schedule(static, 1000)
		for (int i = 1; i<N; i++){
			sum += 4.0/(1.0 + ((i*h)*(i*h)));
		}
		#pragma omp critical
		{
			area += sum;
		}
	}
	area *= h;
	printf("sum: %0.10f\n", area);
}