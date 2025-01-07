// create own buffer

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#define N 10000

int main(){
    MPI_Init(NULL,NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr0, *arr1;
    arr0 = (int*)malloc(sizeof(int)*N);
    arr1 = (int*)malloc(sizeof(int)*N);
 
    if (rank == 0) {
        for(int i=0; i<N; i++){
          arr0[i] = 0;
        }

        int buffer_size = MPI_BSEND_OVERHEAD + N*sizeof(int);
        void* buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
 
        MPI_Bsend(arr0, N, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);

        MPI_Recv(arr1, N, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(int i=0; i<N; i++){
           arr0[i]=arr1[i];
        }
        free(arr1);

        printf("Process 0 received: \n");
        for(int i=N-10; i<N; i++){
           printf("%d ",arr0[i]);
        }
        printf("\n\n");
        free(arr0);

    } else if (rank == 1) {
        for(int i=0; i<N; i++){
          arr1[i] = 1;  
        }

        int buffer_size = MPI_BSEND_OVERHEAD + N*sizeof(int);
        void* buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
 
        MPI_Bsend(arr1, N, MPI_INT, 0, 0, MPI_COMM_WORLD);

        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);

        
        MPI_Recv(arr0, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

 
        for(int i=0; i<N; i++){
           arr1[i]=arr0[i];
        }
        free(arr0);

        printf("Process 1 received: \n");
        for(int i=N-10; i<N; i++){
           printf("%d ",arr1[i]);
        }
        printf("\n\n");
        free(arr1);

    } else {
        printf("I am process %d and I have nothing to do\n", rank);
    }

    MPI_Finalize();
    return 0;
}

