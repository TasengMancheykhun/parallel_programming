#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 1000000
#define T 13

int main(){
    long long sum = 0;
    //long long arr[N] = {0};
    long long *arr;
    arr = malloc(sizeof(long long)*N);

    #pragma omp parallel num_threads(T)
    {

//        long long localsum = 0;

        #pragma omp master
        {
             for (int i=0; i<N; i++) arr[i] = i+1; 
        }

        // #pragma omp for
        // for(int i = 0; i < N; i++){
        //     localsum += arr[i];
        // }

        // #pragma omp critical
        // {
        //     sum += localsum;
        // }

        #pragma omp for reduction( + : sum)     // same thing using reduction
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
