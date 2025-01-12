// Manually do Broadcast
// Receive rank from all other processes and calculate sum of all process rank in rank=0
// Then send the calculated sum back to all other processes and print it 

#include<stdio.h>
#include<mpi.h>
  
int main(){
   
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank != 0){
      MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    
      int totalsum=0;      
      MPI_Recv(&totalsum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      printf("totalsum received from rank=0 in process %d is %d \n", rank, totalsum);
  }
  else{
      int totalsum = 0; 
      totalsum += rank; 
      for(int i = 1; i < size; i++){
          MPI_Recv(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          totalsum += rank;
      }
      printf("totalsum = %d\n", totalsum);

      for(int i=1; i<size; i++){
          MPI_Send(&totalsum, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      }
  }
  
  MPI_Finalize(); 
  return 0;
}
