#include<stdio.h>
#include<omp.h>

int main(){

  #pragma omp parallel num_threads(2)	 
  {
    if (omp_get_thread_num()==0)
        printf("Hello from thread %d\n", omp_get_thread_num());
    else
        printf("Hi from thread %d\n", omp_get_thread_num());
  }
  
  return 0;
} 
