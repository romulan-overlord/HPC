//echo | cpp -fopenmp -dM | grep -i open

#include <stdio.h>
#include <omp.h>
//compiler directive
int main()
{
  int threads= -1, id= -1, cores= -1;

  threads= omp_get_num_threads();
  id= omp_get_thread_num();
  cores= omp_get_num_procs();

  printf("Total cores= %d\n",cores);
  printf("Total threads= %d\n",threads);
  printf("Thread id= %d\n",id);
}
