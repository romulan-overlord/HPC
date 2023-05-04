#include<stdio.h>
#include<omp.h>

int main(){
	int N = 1000;
	int arr[1001] = {};
	arr[0] = 1;
	arr[1] = 1;
	int primeCount = 0, k = 2, mul=0, temp=0, x=0;

	while(1){
		mul = 1;
		temp=k;
		#pragma omp paralle for private(k) reduction(min:k)
		for(int j = k+1; j <= N; j++){
			if(arr[j] != 1){
				k = j;
				break;
			}
		}
		if(k==temp)
			break;
		printf("original k: %d\n", k);
		primeCount++;
		x=k;
		// #pragma omp parallel
		{
			// int threads = 
			// printf("threads: %d\n", omp_get_num_threads());
			// #pragma omp for
			for(mul = 1; mul <= (N+1)/k; mul++){
				// printf("x val: %d", x);
				arr[x] = 1;
				x=k;
				x *=mul;
				if(x > N+1)
					mul=N;
			}
		}
		
	}
	printf("primeCount: %d\n",primeCount);
}