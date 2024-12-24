#include<stdio.h>
#include<unistd.h>
int main(){
  for (int i=0; i<100; i++){
    printf("Hello\n");
    sleep(1);
  }  

  return 0;
}
