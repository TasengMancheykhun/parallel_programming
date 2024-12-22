#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define N 20

void* hello(void* threadid){
    int tid = *(int*)threadid;

    printf("Hello World %d of %d\n",tid,N);
}


int main(){  
 
  pthread_t* t;
  t = malloc(sizeof(pthread_t)*N);  

  for (int i=0; i<N; i++){
      pthread_create(&t[i], NULL, hello, (void*)&i);
  }

  for (int i=0; i<N; i++){ 
      pthread_join(t[i], NULL);
  }
   
  free(t);
  return 0;
}
