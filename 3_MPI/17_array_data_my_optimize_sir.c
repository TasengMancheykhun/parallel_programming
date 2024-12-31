// Sir's way
// Here, array of its chunksize is created in each process. 
// each process calculates its localsum and sends to rank=0
  
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000
  
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
      chunksize += N % size;
  }

  int* arr;
  arr = (int*)malloc(sizeof(int)*(chunksize));     
  
  int index = 0;
  for (int i = start; i < end; i++){                     // each process initialize its small array
      arr[index] = i+1;
      index++;
  }  
  
  index = 0;
  int localsum = 0; 
  for(int i=start; i<end; i++){                         // each process create its own localsum
      localsum += arr[index];
      index++;
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
