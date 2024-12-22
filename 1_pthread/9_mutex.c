//Sum of natural numbers
//Race condition

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define N 1000


pthread_mutex_t mutex;

int sum=0;
int *arr;

void* hello(void* threadid){
    int tid = *(int*)threadid;

    arr[tid] = tid;         

    pthread_mutex_lock(&mutex);
    sum += arr[tid];
    pthread_mutex_unlock(&mutex);
   
    free(threadid);         // best place to free memory
}


int main(){  
   
  pthread_t* t;
  t = malloc(sizeof(pthread_t)*N);  
 
  arr = malloc(sizeof(int)*N);
  
  pthread_mutex_init(&mutex, NULL);
 
  for (int i=0; i<N; i++){
      int* a;
      a = malloc(sizeof(int));
      *a = i;
 
      pthread_create(&t[i], NULL, hello, (void*)a);    
  }
  

  for (int i=0; i<N; i++){ 
      pthread_join(t[i], NULL);
  }
  free(t);


  pthread_mutex_destroy(&mutex);

  for (int i=0;i<N;i++){
     printf("%d ",arr[i]);
  }
  printf("\n");

   
  printf("Sum = %d\n",sum);  


  if(sum + N == (N*(N+1)/2)){
      printf("____Passed____\n");
  }
  else{
      printf("____Failed____\n");   
  }


  free(arr);   
  return 0;
}
