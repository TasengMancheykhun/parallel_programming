#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#define N 100000

int main() {
    MPI_Init(NULL,NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr;
    arr = (int*)malloc(sizeof(int)*N);
 
    if (rank == 0) {
        for(int i=0; i<N; i++){
          arr[i] = 0;
        }
 
        MPI_Sendrecv_replace(arr, N, MPI_INT, 1, 0, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 0 received: \n");
        for(int i=N-10; i<N; i++){
           printf("%d ",arr[i]);
        }
        printf("\n");
        free(arr);

    } else if (rank == 1) {
        for(int i=0; i<N; i++){
          arr[i] = 1;
        }
 
        MPI_Sendrecv_replace(arr, N, MPI_INT, 0, 0, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received: \n");
        for(int i=N-10; i<N; i++){
           printf("%d ",arr[i]);
        }
        printf("\n");
        free(arr);

    } else {
        printf("I am process %d and I have nothing to do\n", rank);
    }

    MPI_Finalize();
    return 0;
}

