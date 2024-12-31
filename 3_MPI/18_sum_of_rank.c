// Receive rank from all other processes and calculate sum of all process rank in rank=0

#include<stdio.h>
#include<mpi.h>
  
int main(){
   
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank != 0){
      MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  else{
      int totalsum = 0; 
      totalsum += rank; 
      for(int i = 1; i < size; i++){
          MPI_Recv(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          totalsum += rank;
      }
      printf("totalsum = %d\n", totalsum);
  }
  
  MPI_Finalize(); 
  return 0;
}
