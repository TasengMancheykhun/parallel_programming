// Broadcast array from rank=0 to other process

#include<mpi.h>
#include<stdio.h>
#define N 10

int main(){

   MPI_Init(NULL, NULL);

   int rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   int arr[N];

   if (rank == 0){
      for(int i=0; i<N; i++){
          arr[i] = i+1;             //Root process initializes the data
      }
   }

   // Broadcast the array from the root process to all processes
   MPI_Bcast(arr, N, MPI_INT, 0, MPI_COMM_WORLD);
    
   printf("\nProcess %d received array \n", rank);
   for(int i=0; i<N; i++){
     printf("%d ", arr[i]);
   } 
   printf("\n");

   MPI_Finalize();
   return 0;
}
