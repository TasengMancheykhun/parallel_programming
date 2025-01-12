#include <mpi.h>
#include <stdio.h>

int main() {
    MPI_Init(NULL,NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buffer;

    if (rank == 0) {
        buffer = 100;

        MPI_Sendrecv(&buffer, 1, MPI_INT, 1, 0, &buffer, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received number %d\n", buffer);
    } else if (rank == 1) {
        buffer = 200;

        MPI_Sendrecv(&buffer, 1, MPI_INT, 0, 0, &buffer, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received number %d\n", buffer);
    } else {
        printf("I am process %d and I have nothing to do\n", rank);
    }

    MPI_Finalize();
    return 0;
}

