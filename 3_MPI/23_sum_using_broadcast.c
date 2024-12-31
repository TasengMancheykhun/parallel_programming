// Send rank value from all process to rank=0 and calculate totalsum of all rank values in rank=0
// Then, use MPI_Bcast to send totalsum in rank=0 to all other process

#include<stdio.h>
#include<mpi.h>
  
int main(){
   
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int totalsum = 0; 

  if (rank != 0){
      MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);                      
  }
  else{
      totalsum = rank;
      int temp                      // we need to make this temp because we need to protect 'rank' variable of rank=0
                                    // otherwise it will get overwritten and rank value will be equal to rank of last process received.
                                    // We want to avoid this, so we create temp and receive rank value from others in temp variable 
 
      for(int i = 1; i < size; i++){
          MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          totalsum += temp;
      }
  }

  MPI_Bcast(&totalsum, 1, MPI_INT, 0, MPI_COMM_WORLD);          // totalsum value is Broadcasted rom rank=0 to all other processes
  
  printf("totalsum received from rank=0 in process %d is %d \n", rank, totalsum);
  MPI_Finalize(); 
  return 0;
}
