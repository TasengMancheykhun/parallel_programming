#include<stdio.h>
#include<omp.h>
#define N 100
#define T 10

int main(){
  int arr[N];

  for (int i=0; i<N; i++) arr[i] = i+1; 

  #pragma omp parallel num_threads(T)	 
  {          
      #pragma omp for
      for (int i = 0; i < N; i++) {
        printf("%d ",arr[i]);
      }
      printf("\n");
 }
 
  return 0;
} 