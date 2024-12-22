//Sum of natural numbers
//Race condition

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define N 1001

int *arr;
int sum=0;

void* hello(void* threadid){
    int tid = *(int*)threadid;

    arr[tid] = tid;         
    sum += tid; 

    free(threadid);         // best place to free memory
}


int main(){  
   
  pthread_t* t;
  t = malloc(sizeof(pthread_t)*N);  
 
  arr = malloc(sizeof(int)*N);
  
  for (int i=0; i<N; i++){
      int* a;
      a = malloc(sizeof(int));
      *a = i;
 
      pthread_create(&t[i], NULL, hello, (void*)a);    
  }
  

  for (int i=0; i<N; i++){ 
      pthread_join(t[i], NULL);
  }


  for (int i=0;i<N;i++){
     printf("%d ",arr[i]);
  }
  printf("\n");

  printf("Sum = %d\n",sum);  

   
  free(t);
  return 0;
}
