#include<stdio.h>
#include<omp.h>
#define N 100
#define T 10

int main(){
  int arr[N];

  for (int i=0; i<N; i++){
      arr[i] = i; 
  }

  #pragma omp parallel num_threads(T)	 
  {
      int chunk_size = N / T;

      int tid = omp_get_thread_num(); 

      int start = tid * chunk_size;
      int end = start + chunk_size;

      if (tid == T - 1) {
          end = N;
      }

      for (int i = start; i < end; i++) {
        printf("%d ",arr[i]);
      }
      printf("\n");

 }
  return 0;
} 