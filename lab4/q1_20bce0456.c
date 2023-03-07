#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    // Initialize MPI environment
    MPI_Init(&argc, &argv); 
    
    // fxn gets the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    // fxn gets the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    //printing the results
    printf("\nHello, world! I am process %d of %d.\n", rank, size);
    MPI_Finalize(); // to finalize MPI environment
    return 0;
}
