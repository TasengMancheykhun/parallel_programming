#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 100

int main(){
 
  int size, rank; 
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
  int chunksize = N/size;
  int start = rank*chunksize;
  int end = start + chunksize;
  if (rank == size-1){
      end = N;
      chunksize += N % size;
  }

  int* sarr;
  sarr = (int*)malloc(sizeof(int)*(chunksize));

  if (rank != 0)
  {
     MPI_Recv(sarr, chunksize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


     printf("process %d: ",rank);
     for(int i=0; i<chunksize; i++){
         printf("%d ", sarr[i]);
     }
     printf("\n");

  }
  else
  {
     int* arr;
     arr = (int*)malloc(sizeof(int)*N);
   
     for(int i = 0; i < N; i++){
         arr[i] = i + 1;
     }
    
     
     for(int ii=0; ii<size; ii++)
     {
        start = ii*chunksize;
        end = start + chunksize;
        if (ii == size-1) end=N;

        int count=0;
        for (int i=start; i<end; i++){
          sarr[count] = arr[i];
          count++;
        }
     
        if (ii == 0)
        { 
            printf("process %d: ",rank);
            for(int i=0; i<chunksize; i++){
                printf("%d ", sarr[i]);
            }
            printf("\n");
        }
        else      
            MPI_Send(sarr, chunksize, MPI_INT, ii, 0, MPI_COMM_WORLD);
     }
 
     free(arr);      
  }
 
  MPI_Finalize();

  free(sarr);

  return 0;
}
