#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i;
    double value = 0.0;
    double sum = 0.0;
    double start_time, end_time;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Set the value of the variable to MPI rank
    value = (double) rank;

    // Ring communication algorithm
    start_time = MPI_Wtime();
    for (i = 1; i < size; i *= 2) {
        if (rank % (2*i) == 0) {
            if (rank + i < size) {
                double temp;
                MPI_Recv(&temp, 1, MPI_DOUBLE, rank+i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                value += temp;
            }
        } else {
            MPI_Send(&value, 1, MPI_DOUBLE, rank-i, 0, MPI_COMM_WORLD);
            break;
        }
    }
    end_time = MPI_Wtime();
    if (rank == 0) {
        printf("Ring communication algorithm: sum = %lf, time = %lf seconds\n", value, end_time - start_time);
    }

    // Hypercube communication algorithm
    start_time = MPI_Wtime();
    for (i = 1; i < size; i *= 2) {
        int partner = rank ^ i;
        if (partner < size) {
            double temp;
            MPI_Recv(&temp, 1, MPI_DOUBLE, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            value += temp;
            MPI_Send(&value, 1, MPI_DOUBLE, partner, 0, MPI_COMM_WORLD);
        }
    }
    end_time = MPI_Wtime();
    if (rank == 0) {
        printf("Hypercube communication algorithm: sum = %lf, time = %lf seconds\n", value, end_time - start_time);
    }

    // Global reduction using MPI Allreduce
    start_time = MPI_Wtime();
    MPI_Allreduce(&rank, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    if (rank == 0) {
        printf("MPI Allreduce: sum = %lf, time = %lf seconds\n", sum, end_time - start_time);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
