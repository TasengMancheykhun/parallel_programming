#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void* hello1(){
    printf("starting thread 1\n");
    sleep(5);
    printf("Ending  thread 1\n");   
}

void* hello2(){
    printf("starting thread 2\n");
    sleep(5);
    printf("Ending  thread 2\n");   
}

void* hello3(){
    printf("starting thread 3\n");
    sleep(5);
    printf("Ending  thread 3\n");   
}

void* hello4(){
    printf("starting thread 4\n");
    sleep(5);
    printf("Ending  thread 4\n");   
}

int main(){
  pthread_t t1, t2, t3, t4;
  
  pthread_create(&t1, NULL, hello1, NULL);

  pthread_create(&t2, NULL, hello2, NULL);
  
  pthread_create(&t3, NULL, hello3, NULL);
  
  pthread_create(&t4, NULL, hello4, NULL);
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  
  return 0;
}
