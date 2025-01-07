// Transfer 3rd column (or index 2 column) from rank 0 to rank 1 

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define N 5

int main(){

  MPI_Init(NULL, NULL);
  int size, rank;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const int count = N;
  const int blocklength = 1;
  const int stride = N;

  int data[N][N];

  MPI_Datatype vector_type;

  MPI_Type_vector(count, blocklength, stride, MPI_INT, &vector_type);

  MPI_Type_commit(&vector_type);

  if (rank==0){
      int temp=1;
      for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            data[i][j] = temp;
            temp++;
        }
      }

      MPI_Send(&data[0][2], 1, vector_type, 1, 0, MPI_COMM_WORLD);

      printf("\nProcess 0 sent data: \n");
      for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
          printf("%d \t",data[i][j]);
        }
        printf("\n");
      }
      printf("\n");

  } else if (rank == 1) {
      for (int i=0; i<N; i++){ 
        for (int j=0; j<N; j++){
          data[i][j] = 0;
        }
      }
      MPI_Recv(data, 1, vector_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      printf("\nProcess 1 received data: \n");
      for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
          printf("%d \t",data[i][j]);
        }
        printf("\n");
      }
      printf("\n");

 }

  MPI_Type_free(&vector_type);
  MPI_Finalize();
 
  return 0;
}

