// Create sub array in each processes and manually gather 
// from all processes and gather in a big array in rank=0 and print it

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 50
  
int main(){
   
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int chunksize = N/size;
  int start = rank*chunksize;
  int end = start + chunksize; 
//  if (rank == size-1){
//      end = N;
//      chunksize += N % size;
//  }

  int* arr;
  arr = (int*)malloc(sizeof(int)*chunksize);     
  
  int index = 0;
  for (int i = start; i < end; i++){                 
      arr[index] = i+1;
      index++;
  }  
  
  if (rank != 0){
      MPI_Send(arr, chunksize, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  else{
      int totalsum = 0;
      int* bigarr = (int*)malloc(sizeof(int)*N);
  
      for(int i = 0; i < chunksize; i++){
         bigarr[i] = arr[i];
      } 

      int s=chunksize;
      for(int i = 1; i < size; i++){
            MPI_Recv(arr, chunksize, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            for (int k = 0; k < chunksize; k++){ 
              bigarr[s] = arr[k]; 
              s++;         
              
//              bigarr[k+i*chunksize] = arr[k];           // another way to create bigger array 
            }  
      }

      printf("Whole array: \n");
      for(int i=0; i<N; i++){ 
        printf("%d ", bigarr[i]);
      }
      printf("\n");

      free(bigarr);
  }
  
  MPI_Finalize();
  
  free(arr);
    
  return 0;
}
