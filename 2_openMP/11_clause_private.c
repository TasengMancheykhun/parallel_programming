#include<stdio.h>
#include<omp.h>

int main(){
  int a = 5;     // shared variable
  #pragma omp parallel private(a) num_threads(4)	 
  {
      int tid = omp_get_thread_num(); 
      printf("thread id  = %d, a = %d\n",tid, a);
  }

  printf("outside, thread id = %d, a = %d\n",omp_get_thread_num(), a);

  return 0;
} 
