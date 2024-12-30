// Here, array of its chunksize is created in each process. 
// Each process calculates its localsum and sends to rank=0

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){


  MPI_Init(NULL, NULL);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int chunksize = N/size;
  int start=0, end=0;

  int* arr;
  if (rank == size-1){
      int rem = N%size;
      arr = (int*)malloc(sizeof(int)*(chunksize+rem));      
  }
  else{ 
      arr = (int*)malloc(sizeof(int)*chunksize);
  }


  start = rank*chunksize;
  end = start + chunksize; 
  if (rank == size-1) end=N;
  
  int count=0;
  for (int i = start; i < end; i++){
      arr[count] = i+1;
      count++;
  }  
  
  int localsum=0; 
  count = 0;
  for(int i=start; i<end; i++){
      localsum += arr[count];
      count++;
  }
  printf("localsum for process %d is %d \n",rank,localsum);


  if (rank != 0){
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
  
  free(arr);
  
  return 0;
}
