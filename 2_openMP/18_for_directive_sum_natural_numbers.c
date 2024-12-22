#include<stdio.h>
#include<omp.h>
#define N 10000000
#define T 13

int main(){
  long long sum=0;
  long long arr[T];
  #pragma omp parallel for firstprivate(sum) num_threads(T)	 
  for (int i = 0; i < N; i++) {
      sum += i;
      int tid = omp_get_thread_num();
      //printf("Thread %d : Sum %f\n", tid, sum);
      arr[tid]=sum;
  }

  long long totsum=0;
  
  for (int i=0; i< T; i++) totsum+=arr[i];
  
  printf("%lld \n",totsum+N);

  return 0;
} 
