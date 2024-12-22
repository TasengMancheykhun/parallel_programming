// Example of task parallelism

#include<stdio.h>
#include<omp.h>

int task(int tid, int a, int b, int c){
    c= a + b+ tid;
    printf("%d\n", c);
}


int main(){
  int a=5;
  #pragma omp parallel num_threads(4)	 
  {
    int b = 6, c = 0;
    int tid = omp_get_thread_num();
    if (tid == 2){
        b=7;
        task(tid,a,b,c);
    }
    else
        task(tid,a,b,c);
  }
  
  return 0;
} 
