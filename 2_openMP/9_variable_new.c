#include<stdio.h>
#include<omp.h>

int main(){
  int a = 5;     // shared variable
  #pragma omp parallel num_threads(10)	 
  {
      int tid = omp_get_thread_num(); 
      if (tid == 0) a = 7;
      printf("thread id  = %d, a = %d\n",tid, a);
  }

  printf("outside, thread id = %d, a = %d\n",omp_get_thread_num(), a);

  return 0;
} 
