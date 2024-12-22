// Reduction using openMP using Reduction clause 
// large data N>100000 

#include<stdio.h>
#include<omp.h>
#define N 1000000000      //max value of int
#define T 13

int main(){
    
    long long sum=0;
    #pragma omp parallel for reduction(+ : sum) num_threads(T)	 
    for (int i=0; i<N; i++){
        sum += i+1;
    }

    printf("Total sum = %lld\n",sum);
  
    if (sum == (N*((N+1)*1L)/2)) printf("___Passed___\n");
    else printf("__Failed__\n");

    return 0;
} 