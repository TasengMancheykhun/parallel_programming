#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){

  int rank, size;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int num1 = 0, num2 = 0, sum = 0;   

  if(rank == 0){                                  // first rank 0 and rank 1 will initialize values
      sum=0;
  } 
  else if(rank == 1){
      sum=1;
  }


  // if rank is not 0 and 1, receive values from its 1st preceeding and 2nd preceeding rank
  if(rank != 0 && rank != 1 ){               
      MPI_Recv(&num1, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(&num2, 1, MPI_INT, rank-2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 
      sum = num1 + num2;     
  }

  
  if(rank != 0 && rank < size-2){                                    // case for upto 3rd last rank, which will send value to 1st next and 2nd next
      MPI_Send(&sum, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);           
      MPI_Send(&sum, 1, MPI_INT, rank+2, 0, MPI_COMM_WORLD);          
  }
  else if(rank == size-2){                                           // case for 2nd last rank which will send value only to 1st next
      MPI_Send(&sum, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
  } 
  else if(rank == 0){ 
      MPI_Send(&sum, 1, MPI_INT, rank+2, 0, MPI_COMM_WORLD);         // case for rank=0, which will send value to 2nd next only i.e rank = 2
  }
 
  printf("rank=%d, value=%d \n",rank, sum);
 
  MPI_Finalize(); 

  return 0;
}
