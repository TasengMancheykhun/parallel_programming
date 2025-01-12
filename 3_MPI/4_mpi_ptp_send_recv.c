#include<stdio.h>
#include<mpi.h>

int main(){

  int myid, size;
  int myval;

  MPI_Init(NULL,NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  if(myid==0){
    myval = 100;
    printf("\nmyid: %d \t myval = %d", myid, myval);
    
    MPI_Send(&myval, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

    printf("\nmyid: %d \t Data sent. \n", myid);
  }
  else if(myid==1){
    myval = 200;
    MPI_Recv(&myval, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("\nmyid: %d \t Data received.", myid);
    printf("\nmyid: %d \t myval = %d", myid);
    printf("\n\nProgram exit!\n",myid, myval);    
  }
  else
    printf("id = %d, myval = %d\n",myid, myval); 

  MPI_Finalize();
  return 0;
}
