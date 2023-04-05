#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define N 65536

int main(int argc, char **argv) {
    int rank, num_procs, i, j;
    double start_time, end_time;
    double local_sum = 0.0, global_sum = 0.0;
    double (*a)[N] = NULL;
    double (*local_a)[N] = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (rank == 0) {
        // Master process initializes the array
        a = (double (*)[N]) malloc(N * N * sizeof(double));
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                a[i][j] = (double)i * (double)j;
            }
        }
        start_time = MPI_Wtime();
    }

    // Distribute the data across the slaves
    int chunk_size = N / num_procs;
    local_a = (double (*)[N]) malloc(chunk_size * N * sizeof(double));

    MPI_Scatter(&a[0][0], chunk_size * N, MPI_DOUBLE, &local_a[0][0], chunk_size * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Each slave performs the computation on its chunk of the data
    for (i = 0; i < chunk_size; i++) {
        for (j = 0; j < N; j++) {
            local_a[i][j] = sqrt(local_a[i][j]);
        }
    }

    // Reduce the data back to the master and sum it
    MPI_Reduce(&local_a[0][0], &local_sum, chunk_size * N, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Master process computes the global sum
        global_sum = local_sum;
        for (i = 1; i < num_procs; i++) {
            MPI_Recv(&local_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            global_sum += local_sum;
        }
        end_time = MPI_Wtime();

        printf("Global sum: %f\n", global_sum);
        printf("Elapsed time: %f seconds\n", end_time - start_time);

        free(a);
    } else {
        // Slaves send their local sum to the master
        MPI_Send(&local_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    free(local_a);
    MPI_Finalize();

    return 0;
}
