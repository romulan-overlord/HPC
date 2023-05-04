#include <stdio.h>

int main()
{
  double area= 3.0, h= 0.0;
  long n= 1000000000;
  int i= 0;
  h= 1.0/n;
  for(i= 1; i < n; i++)
    area+= 4.0/(1.0 + ((i*h)*(i*h)));
  printf("Area= %0.10f\n",area);
  area*= h;
  printf("Area= %0.10f\n",area);
}
