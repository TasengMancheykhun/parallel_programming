#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define N 10000
#define T 13

int main(){
    
    int** a = (int**) malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++){
        a[i] = (int*)malloc(N * sizeof(int));
    }  

    int** b = (int**) malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++){
        b[i] = (int*)malloc(N * sizeof(int));
    }

    int** c = (int**) malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++){
        c[i] = (int*)malloc(N * sizeof(int));
    }

    int** cs = (int**) malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++){
        cs[i] = (int*)malloc(N * sizeof(int));
    }

    //Data creation
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] = j + 1;
            b[i][j] = j + 1;
            c[i][j] = 0;
            cs[i][j] = 0;
        }
    }



    //parallel array addition
    double startTime = omp_get_wtime();
    #pragma omp parallel for num_threads(T)
    for(int i = 0; i < N; i++){                 // only the first loop i is getting parallelized
        for (int j = 0; j<N; j++){              // each thread gets one row  
            c[i][j] = a[i][j] + b[i][j];
        }
    }    
    double endTime = omp_get_wtime();
    double parallelTime = endTime - startTime;

    //Serial array addition
    startTime = omp_get_wtime();
    for(int i = 0; i < N; i++){
        for(int j=0; j< N; j++){
            cs[i][j] = a[i][j] + b[i][j];
        }
    }
    endTime = omp_get_wtime();
    
    double serialTime = endTime - startTime;

    printf("a = \n");
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){  
           printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");  
  
    
    printf("b = \n");
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){  
           printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    printf("\n");  
  

    printf("c = \n");
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){  
           printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    printf("\n");   
    
    
    printf("cs = \n");
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){  
           printf("%d ", cs[i][j]);
        }
        printf("\n");
    }
    printf("\n");  

    printf("\nSerial time = %lf\n", serialTime);
    printf("\nParallel time = %lf\n", parallelTime);



// free the 2d matrix
    for (int i = 0; i < N; i++)   //first free inside container
        free(a[i]);
    free(a);

    for (int i = 0; i < N; i++)
        free(b[i]);
    free(b);

    for (int i = 0; i < N; i++)
        free(c[i]);
    free(c);

    for (int i = 0; i < N; i++)
        free(cs[i]);
    free(cs);
    
    return 0;
}
