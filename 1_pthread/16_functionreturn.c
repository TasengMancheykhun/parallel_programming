#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define T 10


void* hello(void* threadId){
    long tid = (long)threadId;
    long* sum = malloc(sizeof(long));
    *sum=10+tid;

    return (void*)*sum;
}

int main(){
 
    pthread_t* t;
    t = malloc(sizeof(pthread_t) *T);

    long s=0,sum=0;

    for(long i = 0; i < T; i++){
        pthread_create(&t[i], NULL, hello, (void*)i);
    }

    for(long i = 0; i < T; i++){
        pthread_join(t[i], (void**)&sum);
        printf("Local value of each thread = %ld \n",sum);
    }
    
    free(t);

    return 0;
}

