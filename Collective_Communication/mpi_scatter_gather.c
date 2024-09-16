#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    const int root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int scatter_data[size];
    int recv_value;
    int gather_data[size];

    // Root process
    if (rank == root) {
        // Initialize array to scatter
        for (int i = 0; i < size; i++) {
            scatter_data[i] = i * 2; // data: [0, 2, 4, 6,....,(n-1)*2]
        }
        printf("Root process: Data to scatter: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", scatter_data[i]);
        }
        printf("\n");
    }

    // Scatter the data to all processes
    MPI_Scatter(scatter_data, 1, MPI_INT, &recv_value, 1, MPI_INT, root, MPI_COMM_WORLD);

    // Each process modifies the received value
    recv_value += rank;

    // Modified data gathered back to the root process
    MPI_Gather(&recv_value, 1, MPI_INT, gather_data, 1, MPI_INT, root, MPI_COMM_WORLD);

    // Root process prints the gathered data
    if (rank == root) {
        printf("Root process: Gathered data: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", gather_data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
