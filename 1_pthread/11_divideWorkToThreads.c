//Sum of natural numbers
//Race condition

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define N 16
#define T 4 

int *arr;

pthread_mutex_t mutex;

int sum=0;

void* hello(void* threadid){
    int tid = *(int*)threadid;

    pthread_mutex_lock(&mutex);
    sum += tid;
    pthread_mutex_unlock(&mutex);
   
    free(threadid);         // best place to free memory
}


int main(){  
   
  pthread_t* t;
  t = malloc(sizeof(pthread_t)*T);  
  
  pthread_mutex_init(&mutex, NULL);

  arr = malloc(sizeof(int)*N);

  for (int i=0; i<N; i++){
  }


 
  for (int i=1; i<N; i++){
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
   
  printf("Sum = %d\n",sum);  


  if(sum + N == (N*(N+1)/2)){
      printf("____Passed____\n");
  }
  else{
      printf("____Failed____\n");   
  }

  return 0;
}
