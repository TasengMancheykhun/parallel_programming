#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(){

  MPI_Init(NULL, NULL);
  int size, rank;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const int count = 3;
  const int blocklength = 3;
  const int stride = 6;

  int data[15];

  MPI_Datatype vector_type;
  MPI_Type_vector(count, blocklength, stride, MPI_INT, &vector_type);
  MPI_Type_commit(&vector_type);

  MPI_Datatype contiguous_type;
  MPI_Type_contiguous(count, MPI_INT, &contiguous_type);
  MPI_Type_commit(&contiguous_type);
  
  if (rank==0){
      for (int i=0; i<15; i++){
        data[i] = i+1;
      }
  
      MPI_Send(data, 1, vector_type, 1, 0, MPI_COMM_WORLD);
  
      printf("Process 0 sent data: ");
      for (int i=0; i<15; i++){
        printf("%d ",data[i]);
      }
      printf("\n");
  
  } else if (rank == 1) {
      for (int i=0; i<15; i++){
        data[i]=0;
      }
  
      MPI_Recv(data, count, contiguous_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  
      printf("Process 1 received data: ");
      for (int i=0; i<15; i++){
        printf("%d ", data[i]);
      }
      printf("\n");
  }

  MPI_Type_free(&vector_type);
  MPI_Type_free(&contiguous_type);
  MPI_Finalize();
 
  return 0;
}

