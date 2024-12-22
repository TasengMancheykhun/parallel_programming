#include<stdio.h>
#include<omp.h>

int main(){
  int a = 6;
  #pragma omp parallel num_threads(4)	 
  {
      int tid = omp_get_thread_num();
      int b = 6; 
      if (tid == 2) b = 7;
      int c = a + b + tid;
      printf("Value of C for thread id %d is %d\n",tid, c);
  }
  
  return 0;
} 
