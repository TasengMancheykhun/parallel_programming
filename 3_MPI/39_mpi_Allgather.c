#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 20

int main() {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunksize = N / size;
    
    int* arr = NULL; 
    int* localarr = (int*)malloc(chunksize * sizeof(int));

    if (rank == 0) {
        arr = (int*)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            arr[i] = i + 1;
        }
    }

    MPI_Scatter(arr, chunksize, MPI_INT, localarr, chunksize, MPI_INT, 0, MPI_COMM_WORLD);

    int localsum = 0;
    for (int i = 0; i < chunksize; i++){
        localsum += localarr[i];
    }

    int* sumarr = NULL;
    sumarr = (int*)malloc(size * sizeof(int));

    // Allgather gathers localsum from all the processes and insert in 'sumarr' array of size=number_of_processes
    // Then it broadcasts this 'sumarr' to all processes 
    MPI_Allgather(&localsum, 1, MPI_INT, sumarr, 1, MPI_INT, MPI_COMM_WORLD);

    printf("process = %d --> ",rank);
    for(int i=0; i<size; i++){
      printf("%d ", sumarr[i]);
    }
    printf("\n");
    
    if (rank==0){
      free(arr);
    }
 
    free(sumarr);
    free(localarr);

    MPI_Finalize();
    return 0;
}

