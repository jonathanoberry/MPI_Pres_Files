/* based on message passing example from www.mpitutorial.com */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int number;
  if (world_rank == 0) {
    // If we are rank 0, set the number to 13 and send it to process 1
    number = 13;
    MPI_Send(&number, 1, MPI_INT, 1, 0,  MPI_COMM_WORLD);
    // Now we wait to receive 14 back from process 1
    MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);    
    printf("Process 0 received number %d from process 1\n", number);

  } 
  else if (world_rank == 1) {
    // Listen out for the number from process 0
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 1 received number %d from process 0\n", number);
    // Add 1 to it and send it back
    number ++;
    MPI_Send(&number, 1, MPI_INT, 0, 0,  MPI_COMM_WORLD);
  }
  MPI_Finalize();
}
