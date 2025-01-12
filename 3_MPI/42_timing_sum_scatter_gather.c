#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 100000000
  
int main(){
   
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  long long chunksize = N/size;

  long long* arr;
  long long* sarr;
  sarr = (long long*)malloc(sizeof(long long)*chunksize);     
  long long* sumarr;  

  double start_time, end_time;
  
  if(rank == 0){
       arr = (long long*)malloc(sizeof(long long) * N);
       sumarr = (long long*)malloc(sizeof(long long) * size);
       
       for(int i = 0; i < N; i++){
             arr[i] = i + 1;
       }     
  }

  start_time = MPI_Wtime();

  MPI_Scatter(arr, chunksize, MPI_LONG, sarr, chunksize, MPI_LONG, 0, MPI_COMM_WORLD);

  long long localsum=0;
  for(int i = 0; i < chunksize; i++){
      localsum += sarr[i];
  }

  MPI_Gather(&localsum, 1, MPI_LONG, sumarr, 1, MPI_LONG, 0, MPI_COMM_WORLD);
 
  if (rank == 0){
      long long totalsum = 0;
      for(int i=0; i<size; i++){
         totalsum += sumarr[i];
      }

      end_time = MPI_Wtime();   
 
      printf("Totalsum = %lld \n",totalsum);
      printf("Time taken: %f seconds\n", end_time - start_time);

      free(sumarr);
      free(arr);
  }
  
  MPI_Finalize();
  
  free(sarr);
    
  return 0;
}
