#include<stdio.h>
#include<omp.h>

int main(){
  int a = 5; 
  int b = 420; 
  #pragma omp parallel default(none) shared(a) private(b) num_threads(4)	 
  {
      int tid = omp_get_thread_num();
      b = 23; 
      if (tid == 3) a = 7;
      printf("thread id  = %d, a = %d at %p\n", tid, a, &a);
      printf("thread id  = %d, b = %d at %p\n", tid, b, &b);
      
  }

  printf("outside, thread id = %d, a = %d\n",omp_get_thread_num(), a);

  return 0;
} 
