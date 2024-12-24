#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){

  int* arr = (int*) malloc(sizeof(int)*N);

  MPI_Init(NULL, NULL);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank==0){
      for(int i=0; i<N; i++){
          arr[i] = i+1;  
      } 
      
      for (int i=1; i<size; i++){
         MPI_Send(arr, N, MPI_INT, i, 0, MPI_COMM_WORLD);
      }
              
      printf("\nrank: %d \t Data sent.\n\n", rank);                             
  }      
  else{
      MPI_Recv(arr, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      for (int i=0; i<20; i++){
           printf("%d ",arr[i]);
      }
      
      printf("\nrank: %d \t Data received.", rank);
      printf("\nProgram exit!\n\n");
  }
   
  MPI_Finalize();
  
  free(arr);
  
  return 0;
}
