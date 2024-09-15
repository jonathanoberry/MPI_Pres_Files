#include <mpi.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
	int myrank, mysize;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /*find process rank */
	MPI_Comm_size( MPI_COMM_WORLD, &mysize );

    if (myrank == 0) {
		
		printf( "I am %d of %d\n", myrank, mysize );
		printf("ZEEEERRRROOO\n\n\n\n");
		
	} else {
		
		printf("Not Zero\n");
		printf( "I am %d of %d\n\n\n\n", myrank, mysize);
		
	}

	MPI_Finalize();

	}