#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print a message before the barrier
    printf("Process %d out of %d: Before the barrier\n", rank, size);

    sleep(1);
    // Synchronize all processes at this point
    MPI_Barrier(MPI_COMM_WORLD);
    sleep(1);

    // Print a message after the barrier
    printf("Process %d out of %d: After the barrier\n", rank, size);

    MPI_Finalize();
    return 0;
}
