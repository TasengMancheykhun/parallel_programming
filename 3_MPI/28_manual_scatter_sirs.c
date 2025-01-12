#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 100

int main(){

  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
  int chunksize = N/size; 
  int start = rank*chunksize;
  int end = start + chunksize;

  if (rank == size-1){
    end = N;
    chunksize += N%size;
  } 

  int *arr;
  if (rank == 0){
    arr = (int*) malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        arr[i] = i + 1;
    }
    
    for(int i=1; i<size; i++){
        MPI_Send(&arr[i*chunksize], chunksize, MPI_INT, i, 0, MPI_COMM_WORLD);       // mistake ---> rank=0 will send chunksize=N/size for last process as well
    }                                                                                // It should actually be sending chunksize + rem 
  }
  else{
//       printf("rank = %d, chunksize=%d \n", rank, chunksize);

       arr = (int*) malloc(sizeof(int)*chunksize);
       MPI_Recv(arr, chunksize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  printf("rank = %d: ", rank);
  for(int i = 0; i < chunksize; i++){
       printf("%d ",arr[i]);
  }
  printf("\n");
 
  free(arr);

  MPI_Finalize();

  return 0;
}
