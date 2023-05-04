#include <stdio.h>
#include <omp.h>

void do_some_work()
{
}

int main()
{
  int N= 13;
  omp_set_num_threads(5);
  #pragma omp parallel
  {
    int threads= -1, id= -1, i= -1, start= -1, end= -1;
    threads= omp_get_num_threads();
    id= omp_get_thread_num();
    printf("threads: %d\n",threads);
    start= 0;
    end= N;
    for(i= (N * id / threads) + (id > 0 && ((id - 1) <= N % threads) ? 1 : 0); i < ((N * (id + 1) / threads) + (id <= N % threads ? 1 : 0)) ; i++)
    {
      printf("Thread %d: %d\n",id,i);
    }
  }
}
