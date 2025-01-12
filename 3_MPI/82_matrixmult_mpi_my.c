#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<mpi.h>
#define N 3

int main(){

    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
    int chunksize = (N*N)/size;

    int *A, *B, *C;

    // Allocate memory for matrices
    if (rank == 0){
      A = (int *) malloc(N*N*sizeof(int));
      B = (int *) malloc(N*N*sizeof(int));
      C = (int *) malloc(N*N*sizeof(int));
    
      // Initialize matrices
      for (int i = 0; i < N*N; i++){
         A[i] = 1; 
         B[i] = 1;  
      }

//      for (int i = 0; i<N; i++){
//        for (int j = 0; j<N; j++){
//          BB[j*N+i] = B[i*N+j];
//        }
//      } 

    }
    
    int* subA = (int*)malloc(chunksize*sizeof(int));
    int* subC = (int*)malloc(chunksize*sizeof(int));

    double starttime = MPI_Wtime();
    MPI_Scatter(A, chunksize, MPI_INT, subA, chunksize, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);
   
    for (int i=0; i<chunksize; i++){
        for (int j=0; j<chunksize; j++){
            subC[i] += subA[j]*B[i*N+j];
        }
    }

    MPI_Gather(subC, chunksize, MPI_INT, C, chunksize, MPI_INT, 0, MPI_COMM_WORLD);
 
    double endtime = MPI_Wtime();


    // Print result
    if (rank == 0){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i*N+j]);
            }
            printf("\n");
        }
        printf("execution time: %lf\n", endtime - starttime);

        // Free allocated memory
        free(A);
        free(B);
        free(C);
    }

    // Free allocated memory
    free(subA);
    free(subC);

    return 0;
}
