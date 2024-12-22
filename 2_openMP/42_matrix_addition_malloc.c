#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define N 20000
#define T 13

int main(){
    int **a, **b, **c;
    a = (int**) malloc(sizeof(int*) * N);
    b = (int**) malloc(sizeof(int*) * N);
    c = (int**) malloc(sizeof(int*) * N);

    for(int i = 0; i < N; i++){
        a[i] = (int*) malloc(sizeof(int) * N);
        b[i] = (int*) malloc(sizeof(int) * N);
        c[i] = (int*) malloc(sizeof(int) * N);
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] = i + 1;
            b[i][j] = i + 1;
            c[i][j] = 0;
        }
    }

    double starttime = omp_get_wtime();
    #pragma omp parallel for num_threads(T)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    double endtime = omp_get_wtime();
    double paralleltime = endtime - starttime;


    // for(int i = N - 1; i < N; i++){
    //     for(int j = N - 50; j < N; j++){
    //         printf("%d\t", c[i][j]);
    //     }
    //     printf("\n");
    // }

// ------- serial part ---------
    starttime = omp_get_wtime();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    endtime = omp_get_wtime();
    double serialtime = endtime - starttime;

    printf("Parallel time = %lf \n", paralleltime);
    printf("Serial time = %lf \n", serialtime);


    for(int i = 0; i < N; i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
