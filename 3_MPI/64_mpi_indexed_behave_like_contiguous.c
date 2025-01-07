#include<stdio.h>
#include<mpi.h>
#define N 20

int main(){

    MPI_Init(NULL,NULL);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int count = 4;
    int blocklengths[4] = {2,2,2,2};             // for mimicking vector
//    int blocklengths[4] = {5,5,5,5};           // for mimicking contiguous

    int displacements[4] = {0,5,10,15};          // give index for stride length

// To mimic like contiguous, make blocklengths = stride lengths (here created using displacment index at equal interval) 


    int data[N];
    MPI_Datatype indexed_type;
    
    // Create an indexed datatype
    MPI_Type_indexed(count, blocklengths, displacements, MPI_INT, &indexed_type);
    MPI_Type_commit(&indexed_type);
  
    if (rank == 0){
        for (int i=0; i<N; i++){
            data[i] = i+1;
        }
  
        MPI_Send(data, 1, indexed_type, 1, 0, MPI_COMM_WORLD);

        printf("Process 0 sent data: "); 
        for (int i=0; i<N; i++){
            printf("%d ", data[i]);
        }
        printf("\n");

    } else if (rank == 1){
        //Initialize the data array to zero
        for (int i=0; i<N; i++){
            data[i] = 0;
        }
  
        MPI_Recv(data, 1, indexed_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received data: ");
        for (int i=0; i<N; i++){
            printf("%d ",data[i]);
        }
        printf("\n");

    } 

    MPI_Type_free(&indexed_type); 
    MPI_Finalize();
 
    return 0;
}
