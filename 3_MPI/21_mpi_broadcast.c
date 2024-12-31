#include<mpi.h>
#include<stdio.h>


int main(){

   MPI_Init(NULL, NULL);

   int rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   int data;
   if (rank == 0){
       data = 100;             //Root process initializes the data
   }

   // Broadcast the data from the root process to all processes
   // root process here is rank=0
   MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
   printf("Process %d received data %d\n", rank, data);

   MPI_Finalize();
   return 0;
}
