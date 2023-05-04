#include <stdio.h>
#include <omp.h>
#include <limits.h>

int myRed(int a, int b)
{
	printf("in myRed with a: %d   and   b: %d\n", a,b);
	if(a > b)
		return a;
	return b;
}

int main()
{
	int N = 100, max = 0;

	#pragma omp declare reduction (mr:int:omp_out=myRed(omp_out,omp_in)) initializer(omp_priv=INT_MIN)
	#pragma omp parallel reduction(mr:max) num_threads(5)
	{
		#pragma omp for
		for(int i = 1; i <= N; i++){
			if(i > max)
				max = i;
		}
	}
	printf("Calculated max= %d\n",max);
}