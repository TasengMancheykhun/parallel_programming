#include<stdio.h>
#include<omp.h>

int main(){

  printf("Total number of threads before parallel region: %d\n", omp_get_num_threads());
  omp_set_num_threads(6);	             

  #pragma omp parallel num_threads(3)	 
  {
    printf("Hello from first parallel region\n");
    printf("Total number of threads inside first parallel region: %d\n", omp_get_num_threads());
  }

  #pragma omp parallel 
  {
    printf("Hello from second parallel region\n");
    printf("Total number of threads inside second parallel region: %d\n", omp_get_num_threads());
  }

  printf("Total number of threads after parallel region: %d\n", omp_get_num_threads());
  return 0;
} 
