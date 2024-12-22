#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* task(){
    printf("starting thread \n");
    sleep(3);
    printf("Ending  thread \n");   
}


int main(){  

  int N; 
  
  printf("Enter the total threads:\n");
  scanf("%d",&N); 
    
  pthread_t t[N];  

  for (int i=0; i<N; i++){
      pthread_create(&t[i], NULL, task, NULL);
  }

  for (int i=0; i<N; i++){ 
      pthread_join(t[i], NULL);
  }
 
  return 0;
}
