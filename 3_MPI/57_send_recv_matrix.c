#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 3

int main(){

//  int* arr = (int*) malloc(sizeof(int)*N*N);
  
  int arr[N][N];  

  MPI_Init(NULL, NULL);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank==0){
      for(int i=0; i<N; i++){
          for(int j=0; j<N; j++){
              arr[i][j] = 1;  
          }
      } 
      
      MPI_Send(arr, N*N, MPI_INT, 1, 0, MPI_COMM_WORLD);

      for (int i=0; i<N; i++){
           for (int j=0; j<N; j++){
               printf("%d ",arr[i][j]);
           }
           printf("\n");
      }
              
      printf("\nrank: %d \t Data sent.\n", rank);                             
  }      
  else if (rank == 1){
      MPI_Recv(arr, N*N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      for (int i=0; i<N; i++){
           for (int j=0; j<N; j++){
               printf("%d ",arr[i][j]);
           }
           printf("\n");
      }
      
    printf("\nrank: %d \t Data received.", rank);
    printf("\nProgram exit!\n");
  }
   
  MPI_Finalize();
  
//  free(arr);
  
  return 0;
}
