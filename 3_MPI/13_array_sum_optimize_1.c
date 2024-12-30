// Here, full array is create by each process
// Each process will sum its chunk of array data
// Each process will send its local sum to rank=0
// Rank=0 will sum its own localsum and all localsum received from other processes
// and calculate the total sum

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(){
    int size, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int n = 1000;

    int arr[n];

    for(int i = 0; i < n; i++){
        arr[i] = i + 1;
    }

    int chunksize = n / size;
    int start = rank * chunksize;
    int end = start + chunksize;
    if(rank == size - 1){
        end = n;
    }

    int localsum = 0;
    for(int i = start; i < end; i++){
        localsum += arr[i];
    }

    if(rank != 0){
        MPI_Send(&localsum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else{
        int totalsum = 0;
        totalsum += localsum;
        for(int i = 1; i < size; i++){
            MPI_Recv(&localsum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalsum += localsum;
        }
        printf("totalsum = %d\n", totalsum);
    }

    MPI_Finalize();
    return 0;
}

