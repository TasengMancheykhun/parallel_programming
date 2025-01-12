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

  int chunksize = N/size;

  if(rank==0){
      for(int i=0; i<N; i++){
          arr[i] = i+1;  
      } 
      
      for (int i=1; i<size; i++){
         MPI_Send(arr, N, MPI_INT, i, 0, MPI_COMM_WORLD);
      }


// For rank=0 localsum
// ------------------------------------
      int sum=0, localsum=0;
      
      int start = rank*chunksize;
      int end = start + chunksize;      

      for(int i=start; i<end; i++){
        localsum += arr[i];
      }
      sum += localsum;
// -------------------------------------

      printf("localsum of process 0 = %d \n", localsum);

      for (int i=1; i<size; i++){       
         MPI_Recv(&localsum, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         
         printf("localsum of process %d = %d \n",i, localsum);  

         sum += localsum;
      }
    
      printf("Total Sum: %d \n",sum);              
                               
  }      
  else{
      MPI_Recv(arr, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      int start = rank*chunksize;
      int end = start + chunksize;
      
      int localsum = 0;

      if (rank == size-1) end=N;

      for(int i=start; i<end; i++){
        localsum += arr[i];
      }
 
      MPI_Send(&localsum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }
   
  MPI_Finalize();
  
  free(arr);
  
  return 0;
}
