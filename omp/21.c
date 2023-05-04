#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{
  int N= 10, i= -1;
  // omp_set_num_threads(1);
  #pragma omp parallel
  {
    int id= omp_get_thread_num();
    printf("No. of threads: %d", omp_get_num_threads());

    #pragma omp for schedule(static)
    for(i= 0; i < N; i++){
      printf("Thread %d got %d\n",id,i);
      // sleep(N-i);
    }

  }
}
