#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    int local_value, global_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // ESet local value to rank
    local_value = rank;

    // MPI_Allreduce sums the local values across all processes
    MPI_Allreduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Each process now has the global sum
    printf("Process %d: The sum of all ranks is %d\n", rank, global_sum);

    MPI_Finalize();
    return 0;
}
