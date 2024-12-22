// Reduction using openMP using Reduction clause 
// Comparing timings  

#include<stdio.h>
#include<omp.h>
#define N 1000000000      //max value of int
#define T 13

int main(){
    
    long long sum=0;
    double parallelTime, serialTime;

    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(+ : sum) num_threads(T)	 
    for (int i=0; i<N; i++){
        sum += i+1;
    }
    double endTime = omp_get_wtime();
    parallelTime = endTime - startTime;


    startTime = omp_get_wtime();
    long long serialsum = 0;
    for(int i = 0; i < N; i++){
        serialsum += i + 1;
    }
    endTime = omp_get_wtime();
    serialTime = endTime - startTime;

    printf("Total sum = %lld\n",sum);
    
    printf("Time taken by parallel = %lf\n", parallelTime);
    printf("Time taken by serial = %lf\n", serialTime);

    if (sum == (N*((N+1)*1L)/2)) printf("___Passed___\n");
    else printf("__Failed__\n");

    return 0;
} 