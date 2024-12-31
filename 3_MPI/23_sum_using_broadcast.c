// send rank value from all process to rank=0 and calculate sum in rank=0

#include<stdio.h>
#include<mpi.h>
  
int main(){
   
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int totalsum = 0; 

  if (rank != 0){
      int r = rank;                   // we need to do this r = rank because we need to protect 'rank' variable, it will get overwritten otherwise
      MPI_Send(&r, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);                      
  }
  else{
      totalsum = rank; 
      for(int i = 1; i < size; i++){
          int r = rank;
          MPI_Recv(&r, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          totalsum += r;
      }
  }

  MPI_Bcast(&totalsum, 1, MPI_INT, 0, MPI_COMM_WORLD);
  
  printf("totalsum received from rank=0 in process %d is %d \n", rank, totalsum);
  MPI_Finalize(); 
  return 0;
}
