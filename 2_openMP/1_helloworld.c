#include<stdio.h>
#include<unistd.h>
#include<omp.h>

int main(){
  #pragma omp parallel
  {
    printf("Hello World\n");
  }
  
  return 0;
}
