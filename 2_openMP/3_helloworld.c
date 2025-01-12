#include<stdio.h>
#include<unistd.h>
#include<omp.h>

int
main ()
{
  omp_set_num_threads (6);	           // it will create 4 threads
  #pragma omp parallel num_threads(3)	 // don't put semicolon or curly bracket '{' at end here
  {
    printf ("Hello World Warz\n");
  }

  return 0;
}
