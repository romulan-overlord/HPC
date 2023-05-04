#include <stdio.h>
#include <omp.h>

int main()
{
  double area= 3.0, h= 0.0;
  // long n= 1000000000;
  long n=100;
  h= 1.0/n;
  double areaArr[] = {0.0,0.0};
  #pragma omp parallel for
    for(int i= 1; i < n; i++)
      areaArr[omp_get_thread_num()]= 4.0/(1.0 + ((i*h)*(i*h)));

  area += areaArr[0] + areaArr[1];
  area*= h;
  printf("Area= %0.10f\n",area);
}
