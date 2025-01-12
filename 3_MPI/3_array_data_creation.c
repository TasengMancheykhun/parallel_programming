// create data of array parallelly and also print them.
// Each process has its own PRIVATE MEMORY

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){

  long long* arr = (long long*) malloc(sizeof(long long)*N);

  MPI_Init(NULL, NULL);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int chunksize = N/size;
  int start = rank*chunksize;
  int end = start+chunksize;

  if (rank == size-1) end=N;

  for(int i=start; i<end; i++){
    arr[i] = i+1;

    printf("%lld ",arr[i]);              // every process/rank will print its own data which it created. Each cannot print other process
  }                                      // data. Every process has its own PRIVATE data. One process CANNOT access other process data 
                                         // and so can't print it.    
//  if (rank==0){
//    for(int i=0; i<N; i++){
//      printf("%lld ",arr[i]);
//    }
//  }
  printf("\n");
  
  MPI_Finalize();
  
  free(arr);
  
  return 0;
}
