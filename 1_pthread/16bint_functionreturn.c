#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define T 10


void* hello(){
    int sum;
    sum=10;

    return (void*)sum;
}

int main(){
 
    pthread_t* t;
    t = malloc(sizeof(pthread_t) *T);

    int sum=0;

    for(long i = 0; i < T; i++){
        pthread_create(&t[i], NULL, hello, NULL);
    }

    for(long i = 0; i < T; i++){
        pthread_join(t[i], (void**)&sum);
        printf("Local value of each thread = %d \n",sum);
    }
    
    free(t);

    return 0;
}

