// Example of task parallelism

#include<stdio.h>
#include<omp.h>

int task1(int tid){
    printf("Executing task1 by thread %d\n", tid);
}

int task2(int tid){
    printf("Executing task2 by thread %d\n", tid);
}

int main(){

  #pragma omp parallel num_threads(2)	 
  {
    int tid = omp_get_thread_num();
    if (tid==0)
        task1(tid);
    else
        task2(tid);
  }
  
  return 0;
} 
