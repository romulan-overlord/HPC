#include<stdio.h>
#include<omp.h>
#include<unistd.h>

int main()
{
	#pragma omp parallel
	{
		int rank = omp_get_thread_num();
		printf("%d be wildin'\n", rank);
		// #pragma omp for nowait
		// #pragma omp master
		// for(int i = 0; i < 5; i++){
		// 	printf("%d finna wait for %d\n",rank, i);
		// 	sleep(i);
		// }
		#pragma omp critical
		{
			printf("%d finna wait sum more: \n", rank);
			sleep(rank + 2);	
		}
		// #pragma omp barrier
		printf("%d got past barrier\n", rank);
	}
}