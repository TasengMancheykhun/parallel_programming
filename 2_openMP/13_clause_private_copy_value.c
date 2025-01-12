#include<stdio.h>
#include<omp.h>

int main(){
  int a = 5;     // shared variable
  #pragma omp parallel firstprivate(a) num_threads(4)	 
  {
      int tid = omp_get_thread_num(); 
      if (tid == 3) a = 7;
      printf("thread id  = %d, a = %d\n", tid, a);
  }

  printf("outside, thread id = %d, a = %d\n",omp_get_thread_num(), a);

  return 0;
} 



// printing address to understand that private variable 
// created in different address
/*
int main(){
  int a = 5;     // shared variable
  #pragma omp parallel firstprivate(a) num_threads(4)	 
  {
      int tid = omp_get_thread_num(); 
      if (tid == 3) a = 7;
      printf("thread id  = %d, a = %d, address=%p\n", tid, a, &a);
  }

  printf("outside, thread id = %d, a = %d, address=%p\n",omp_get_thread_num(), a, &a);

  return 0;
} 
*/
