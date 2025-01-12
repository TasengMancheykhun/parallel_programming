// Reduction using openMP using for directive
// large data N>100000 

#include<stdio.h>
#include<omp.h>
#define N 1000000000      //max value of int
#define T 13

int main(){

    long long sum[T];
    #pragma omp parallel num_threads(T)	 
    {
        int tid = omp_get_thread_num();
        long long localsum=0;
        #pragma omp for   
        for (int i=0; i<N; i++) localsum += i+1;
        
        sum[tid] = localsum;
    }

  long long totalSum = 0;
  for (int i=0; i < T; i++) totalSum += sum[i];

  printf("Total sum = %lld\n",totalSum);
  
  if (totalSum == (N*((N+1)*1L)/2)) printf("___Passed___\n");
  else printf("__Failed__\n");

  return 0;
} 
