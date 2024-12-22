#include<stdio.h>
#include<omp.h>
#define N 100
#define T 13

int main(){
    long long sum = 0;
    long long arr[N] = {0};

    #pragma omp parallel num_threads(T)
    {

        long long localsum = 0;

        #pragma omp master
        {
             for (int i=0; i<N; i++) arr[i] = i+1; 
        }

        #pragma omp for
        for(int i = 0; i < N; i++){
            localsum += arr[i];
        }

        #pragma omp critical
        {
            sum += localsum;
        }

        // #pragma omp for reduction( + : sum)     // same thing using reduction
        // for(int i = 0; i < N; i++){
        //     sum += arr[i];
        // }

    }

    printf("Calculated sum = %lld\n", sum);
    long long expectedSum = (N * ((N + 1) * 1L) / 2);
    printf("Expected sum = %lld\n", expectedSum);
    if(sum == expectedSum){
        printf("_____Passed_____\n");
    }
    else printf("_____Failed_____\n");

    return 0;
}
