#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define N 10000
#define T 13

int main(){
    int *a, *b, *c, *cs;
    a = (int *) malloc(N*N*sizeof(int));
    b = (int *) malloc(N*N*sizeof(int));
    c = (int *) malloc(N*N*sizeof(int));
    cs = (int *) malloc(N*N*sizeof(int));

    //Data creation
    for(int i = 0; i < N; i++){
        for(int j = 0; j<N; j++){
            a[i*N+j] = j + 1;
            b[i*N+j] = j + 1;
            c[i*N+j] = 0;
            cs[i*N+j] = 0;
        }
    }

    //parallel array addition 
    double startTime = omp_get_wtime(); 
    #pragma omp parallel for num_threads(T) 
    for(int i = 0; i < N; i++){ 
        for (int j = 0; j<N; j++){ 
            c[i*N+j] = a[i*N+j] + b[i*N+j]; 
        } 
    } 
    
    double endTime = omp_get_wtime();
    double parallelTime = endTime - startTime;

    //Serial array addition
    startTime = omp_get_wtime();
    for(int i = 0; i < N; i++){
        for(int j=0; j< N; j++){
            cs[i*N+j] = a[i*N+j] + b[i*N+j];
        }
    }
    endTime = omp_get_wtime();
    
    double serialTime = endTime - startTime;

    printf("a = \n");
    for(int i = 0; i < 20; i++){
        printf("%d ", a[i]);
    }
    printf("\n");  
   
    printf("b = \n");
    for(int i = 0; i < 20; i++){
        printf("%d ", b[i]);
    }
    printf("\n");  

  
    printf("parallel = \n");
    for(int i = 0; i < 20; i++){
        printf("%d ", c[i]);
    }
    printf("\n");  

    printf("serial = \n");
    for(int i = 0; i < 20; i++){
        printf("%d ", cs[i]);
    }
    printf("\n");    
    
    printf("\nSerial time = %lf\n", serialTime);
    printf("\nParallel time = %lf\n", parallelTime);

    free(a); free(b); free(c); free(cs);

    return 0;
}
