#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define T 20

int main() {
    const int n = 600;

    // Allocate memory for matrices
    int* A = (int *)malloc(n*n * sizeof(int));
    int* B = (int *)malloc(n*n * sizeof(int));
    int* C = (int *)malloc(n*n * sizeof(int));

    // Initialize matrices
    #pragma omp parallel for num_threads(T)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            A[j + i*n] = 1;
            B[j + i*n] = 1;
            C[j + i*n] = 0;
        }
    }

//    # pragma omp barrier

    double starttime = omp_get_wtime();
    #pragma omp parallel for firstprivate(A,B,C) num_threads(T)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n ; k++) {
                C[j+i*n] += A[k+i*n] * B[j+k*n];
            }
        }
    }

    double endtime = omp_get_wtime();


    // Print result
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[j+i*n]);
        }
        printf("\n");
    }
    printf("execution time: %lf\n", endtime - starttime);

    // Free allocated memory
    free(A);
    free(B);
    free(C);

    return 0;
}
