// tag
// system buffer

#include <stdio.h>
#include <mpi.h>


int main(){

  int rank, size;
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int data1, data2, data3, data4, data5;
  if (rank == 0){
    data1 = 100;
    data2 = 200;
    data3 = 300;
    data4 = 400;
    data5 = 500;

    MPI_Send(&data1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&data2, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&data3, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&data4, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&data5, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }
  else if(rank == 1){
    MPI_Recv(&data1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&data2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&data3, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&data4, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&data5, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("process %d received data1 %d \n", rank, data1);
    printf("process %d received data2 %d \n", rank, data2);
    printf("process %d received data3 %d \n", rank, data3);
    printf("process %d received data4 %d \n", rank, data4);
    printf("process %d received data5 %d \n", rank, data5);
  }
  
  MPI_Finalize();

  return 0;
}
