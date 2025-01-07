#include<mpi.h>
#include<stdio.h>

int main(){

  MPI_Init(NULL,NULL);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int senddata, recvdata;
  if (rank==0){
    senddata = 100;

    MPI_Sendrecv(&senddata, 1, MPI_INT, 1, 0, &recvdata, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process 0 sent %d and received number %d\n",senddata, recvdata);

  }else if (rank == 1){
    senddata = 300;
    
    MPI_Sendrecv(&senddata, 1, MPI_INT, 0, 0, &recvdata, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 
    printf("Process 1 received %d and sent number %d\n",recvdata, senddata);

  }else{
    printf("I am process %d and I have nothing to do\n", rank);
  }  

  MPI_Finalize();

  return 0;
}
