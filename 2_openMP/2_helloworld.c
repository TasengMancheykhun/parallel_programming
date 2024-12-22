#include<stdio.h>
#include<unistd.h>
#include<omp.h>

int main(){
  omp_set_num_threads(6);         // it will create 4 threads
  #pragma omp parallel 
  {
    printf("Hello World me\n");
  }
  
  return 0;
}
