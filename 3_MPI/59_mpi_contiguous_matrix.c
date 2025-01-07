// Using contiguous data type to send matrix 

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 5

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }


    const int count = N;
    int data[N][N];
    MPI_Datatype contiguous_type;

    // create a contiguous datatype
    MPI_Type_contiguous(count, MPI_INT, &contiguous_type);
    MPI_Type_commit(&contiguous_type);
    

    if (rank == 0) {
        int temp = 1;
        // Initialize the data array with some values
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                data[i][j] = temp;
                temp++;
            }
        }

        MPI_Send(data, N , contiguous_type, 1, 0, MPI_COMM_WORLD);

        printf("Process 0 sent data: \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d\t", data[i][j]);
            }
            printf("\n");
        }
        printf("\n");

    } else if (rank == 1) {

        MPI_Recv(data, N, contiguous_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received data: \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d\t", data[i][j]);
            }
            printf("\n");
        }
    }


    MPI_Type_free(&contiguous_type);                // free the data type you created    

    MPI_Finalize();
    return 0;
}
