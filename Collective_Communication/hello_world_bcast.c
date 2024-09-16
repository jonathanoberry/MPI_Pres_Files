#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  char message[20];
  int  i, rank, size;
  MPI_Status status;
  int root = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Root process sets the broadcast message
  if (rank == root)
  {
    strcpy(message, "Hello, world");
  }

  // Message broadcasted to other processes
  MPI_Bcast(message, 12, MPI_CHAR, root, MPI_COMM_WORLD);
  printf( "Message from process %d : %s\n", rank, message);

  MPI_Finalize();
}