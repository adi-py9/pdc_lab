#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char name[MPI_MAX_PROCESSOR_NAME];
    int len;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // fxn gets the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // fxn gets the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Get_processor_name(name, &len);
    
    printf("\nHello from processor %d of %d on %s\n", rank, size, name);
    MPI_Finalize();// to finalize MPI environment
    return 0;
}
