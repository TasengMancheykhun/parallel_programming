#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 100000000

int main(){

  int rank, size;
  MPI_Init(NULL,NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  
  long long chunksize = N/size;

  long long* arr;
  long long* localarr = (long long*) malloc(sizeof(long long)*chunksize);

  double start_time, end_time;

  if (rank == 0){
    arr = (long long*)malloc(sizeof(long long)*N);
    for(int i=0; i<N; i++){
      arr[i] = i+1; 
    }
  }

  if(rank==0) start_time = MPI_Wtime();  

  MPI_Scatter(arr, chunksize, MPI_LONG, localarr, chunksize, MPI_LONG, 0, MPI_COMM_WORLD);

  long long localsum=0;  
  for (int i=0; i<chunksize; i++){
    localsum += localarr[i]; 
  }
  
  long long finalsum;

  MPI_Reduce(&localsum, &finalsum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

  MPI_Bcast(&finalsum, 1, MPI_LONG, 0, MPI_COMM_WORLD);

  printf("rank = %d, total sum = %lld \n", rank, finalsum);

  if(rank == 0){
    end_time = MPI_Wtime();

    printf("Time taken: %f seconds\n", end_time - start_time);
 
    free(arr);
  }   
  
  free(localarr);
  MPI_Finalize();
  
  return 0;
}
