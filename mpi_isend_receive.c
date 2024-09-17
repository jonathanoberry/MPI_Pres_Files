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
  
  MPI_Request request;
  int number;
  if (world_rank == 0) {
    // If we are rank 0, set the number to 13 and send it to process 1
    number = 13;
    MPI_Isend(&number, 1, MPI_INT, 1, 0,  MPI_COMM_WORLD, &request);
    printf("Sent the number %d to process 1 \n", number);
    // Now do something else
    for(int i=0; i<500; i+=29){
        number = number + i;
        printf("Added %d, now the number is %d \n", i, number);
    }
    printf("Addition loop finished. \n");
    MPI_Wait(&request, MPI_STATUS_IGNORE);
  } 
  else if (world_rank == 1) {
    // Listen out for the number from process 0
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 1 received number %d from process 0\n", number);
  }
  MPI_Finalize();
}