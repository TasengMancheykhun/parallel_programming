#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 1000000
#define T 13

int main(){
    
    long long *arr; 
    arr = malloc(sizeof(long long)*N);

    long long sum = 0;

    #pragma omp parallel num_threads(T)
    {
        #pragma omp for
        for(int i = 0; i < N; i++){ 
            arr[i] = i+1; 
        }

        // No need of barrier here, because 
    
        #pragma omp for reduction( + : sum)   
        for(int i = 0; i < N; i++){
            sum += arr[i];
        }
    }
    
    printf("Calculated sum = %lld\n", sum);
    long long expectedSum = (N * ((N + 1) * 1L) / 2);
    printf("Expected sum = %lld\n", expectedSum);
    if(sum == expectedSum){
        printf("_____Passed_____\n");
    }
    else printf("_____Failed_____\n");

    free(arr);

    return 0;
}
