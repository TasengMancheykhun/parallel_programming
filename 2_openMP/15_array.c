#include<stdio.h>
#include<omp.h>
#define N 5

int main(){
  int arr[N];

  for (int i=0;i<N;i++){
      arr[i] = i; 
  }

  #pragma omp parallel num_threads(5)	 
  {

      // for (int i=0; i<N; i++){
      //   printf("%d ",arr[i]);
      // }
      // printf("\n");

      int tid = omp_get_thread_num(); 
      printf("%d ",arr[tid]);
      printf("\n");
 }
  return 0;
} 