// Reduction using openMP using Reduction clause 
// Comparing timings  

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 1000000000      //max value of int
#define T 13

int main(){

//  long long const N = 10000000000;     
    long long *arr1, *arr2;
    long long *parr, *sarr;

    arr1 = malloc(sizeof(long long)*N);
    arr2 = malloc(sizeof(long long)*N);
    
    parr = malloc(sizeof(long long)*N);
    sarr = malloc(sizeof(long long)*N);

    for (int i=0; i<N; i++){
        arr1[i] = i+1;
        arr2[i] = i+1;
    }

    double parallelTime, serialTime;

    double startTime = omp_get_wtime();
    #pragma omp parallel for num_threads(T)	 
    for (int i=0; i<N; i++){
        parr[i] = arr1[i] + arr2[i];
    }    
    double endTime = omp_get_wtime();
    parallelTime = endTime - startTime;


    startTime = omp_get_wtime();
    long long serialsum = 0;
    for(int i = 0; i < N; i++){
        sarr[i] = arr1[i] + arr2[i];
    }
    endTime = omp_get_wtime();
    serialTime = endTime - startTime;

    for (int i=N-20; i<N; i++){
        printf("%lld %lld \n", sarr[i], parr[i]);
    }

    printf("Time taken by parallel = %lf s\n", parallelTime);
    printf("Time taken by serial = %lf s\n", serialTime);

    free(arr1); free(arr2); free(sarr); free(parr);

    return 0;
} 