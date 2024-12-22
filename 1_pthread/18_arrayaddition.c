#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define T 5
#define N 28

int* arr1;                // dynamic array  
int* arr2; 
//int arr1[N], arr2[N];   // static array
int* arr;

void* hello(void* threadid){
    long tid = (long)threadid;
    int chunksize = N/T;

    int start = tid*chunksize;
    int end = start+chunksize;
    
    if (tid == T-1){
        end = N;
    }

    for (int i=start; i<end; i++){
        arr[i] = arr1[i] + arr2[i];
    }
}

int main(){
    pthread_t* t;
    t = malloc(sizeof(pthread_t) * T);

    arr = malloc(sizeof(int)*N);     // dynamic total array

    arr1 = malloc(sizeof(int)*N);    // dynamic array
    arr2 = malloc(sizeof(int)*N);

    for (int i=0; i<N; i++){
        arr1[i] = i+1;
        arr2[i] = i+2;
    }
    
//----------- printing arr1 and arr2 ------------
    printf("arr1: \n");
    for (int i=0; i<N; i++){
        printf("%d ",arr1[i]);
    }
    printf("\n");

    printf("arr2: \n");
    for (int i=0; i<N; i++){
        printf("%d ",arr2[i]);
    }
    printf("\n");
// ---------------------------------
    
    for(long i = 0; i < T; i++){
        pthread_create(&t[i], NULL, hello, (void*)i);
    }
    
    for(long i = 0; i < T; i++){
        pthread_join(t[i], NULL);
    }
// --------- print addition ----------
    printf("arr3: \n");
    for (int i=0; i<N; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
// -----------------------------------

    free(t);
    free(arr);
    free(arr1);
    free(arr2);
    return 0;
}
