#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, local_value, sum_reduce, sum_scan;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // local value is the process rank.
    local_value = rank;

    // MPI_Reduce sums the values of all ranks and store the result in the root process
    MPI_Reduce(&local_value, &sum_reduce, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Printing the result of MPI_Reduce on the root process
    if (rank == 0) {
        printf("Total sum using MPI_Reduce (in process 0): %d\n", sum_reduce);
    }

    // MPI_Scan computes the prefix sum across all processes
    MPI_Scan(&local_value, &sum_scan, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Printing the result of MPI_Scan on each process
    printf("Prefix sum using MPI_Scan (in process %d): %d\n", rank, sum_scan);

    MPI_Finalize();
    return 0;
}
