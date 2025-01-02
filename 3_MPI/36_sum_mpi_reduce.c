#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 100

int main(){

  int rank, size;
  MPI_Init(NULL,NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  
  int chunksize = N/size;

  int* arr;
  int* localarr = (int*) malloc(sizeof(int)*chunksize);

  if (rank == 0){
    arr = (int*)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
      arr[i] = i+1; 
    }
  }

  MPI_Scatter(arr, chunksize, MPI_INT, localarr, chunksize, MPI_INT, 0, MPI_COMM_WORLD);

  int localsum=0;  
  for (int i=0; i<chunksize; i++){
    localsum += localarr[i]; 
  }
  
  int finalsum;
  MPI_Reduce(&localsum, &finalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  printf("rank = %d, total sum = %d \n", rank, finalsum);

  if(rank == 0){
    free(arr);
  } 
  
  free(localarr);
  MPI_Finalize();
  
  return 0;
}
