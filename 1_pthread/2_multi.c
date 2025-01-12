#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define N 10

void* task(){
    printf("starting thread \n");
    sleep(2);
    printf("Ending  thread \n");   
}


int main(){  
     
  pthread_t t;  

  for (int i=0; i<N; i++){
      pthread_create(&t, NULL, task, NULL);
  }

  pthread_join(t, NULL);
 
  return 0;
}
