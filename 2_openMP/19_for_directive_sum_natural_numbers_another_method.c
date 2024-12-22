#include<stdio.h>
#include<omp.h>
#define N 10000000
#define T 13

int main(){
  long long arr[T]={0};
  
  #pragma omp parallel for num_threads(T)	 
  for (int i = 1; i <= N; i++) {
      int tid = omp_get_thread_num();
      //printf("Thread %d : Sum %f\n", tid, sum);
      arr[tid] += i;
  }

  long long totsum = 0;

  for (int i=0; i < T; i++) totsum += arr[i];
  
  printf("%lld \n",totsum);
  
  return 0;
} 