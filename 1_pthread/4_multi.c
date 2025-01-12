#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* task1(){
    printf("starting thread onehalf\n");
    sleep(3);
    printf("Ending  thread onehalf\n");   
}

void* task2(){
    printf("starting thread  secondhalf\n");
    sleep(3);
    printf("Ending  thread secondhalf\n");   
}



int main(){  

  int N; 
  
  printf("Enter the total threads:\n");
  scanf("%d",&N); 
    
  pthread_t t[N];  

  for (int i=0; i<N; i++){
      if (i<N/2){
          pthread_create(&t[i], NULL, task1, NULL);
      }
      else{
          pthread_create(&t[i], NULL, task2, NULL);
      }
  }

  for (int i=0; i<N; i++){ 
      pthread_join(t[i], NULL);
  }
   

  return 0;
}
