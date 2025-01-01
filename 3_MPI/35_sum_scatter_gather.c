// Combine scatter and gather to calculate sum of natural numbers
// Create array in rank = 0
// Use MPI_Scatter to scatter chunks to other processes
// calculate localsum at each process
// Use MPI_Gather to gather localsum to rank=0
// lastly calculate totalsum

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 20
  
int main(){
   
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int chunksize = N/size;

  int* arr;
  int* sarr;
  sarr = (int*)malloc(sizeof(int)*chunksize);     
  int* sumarr;  
  
  if(rank == 0){
       arr = (int*)malloc(sizeof(int) * N);
       sumarr = (int*)malloc(sizeof(int) * size);
       
       for(int i = 0; i < N; i++){
             arr[i] = i + 1;
       }     
  }

  MPI_Scatter(arr, chunksize, MPI_INT, sarr, chunksize, MPI_INT, 0, MPI_COMM_WORLD);

  int localsum=0;
  for(int i = 0; i < chunksize; i++){
      localsum += sarr[i];
  }

  MPI_Gather(&localsum, 1, MPI_INT, sumarr, 1, MPI_INT, 0, MPI_COMM_WORLD);
 
  if (rank == 0){
      int totalsum = 0;
      printf("localsum array: ");
      for(int i=0; i<size; i++){
         printf("%d ",sumarr[i]);
         totalsum += sumarr[i];
      }
      printf("\n");
      printf("Totalsum = %d \n",totalsum);
      free(sumarr);
      free(arr);
  }
  
  MPI_Finalize();
  
  free(sarr);
    
  return 0;
}
