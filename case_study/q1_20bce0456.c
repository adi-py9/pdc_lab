#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10000 // number of data points
#define NUM_BINS 100 // number of bins in the histogram
#define MIN_VAL 0.0 // minimum value in data range
#define MAX_VAL 1.0 // maximum value in data range

int main(int argc, char **argv) {
    int rank, num_procs, i, j;
    double data[N];
    int counts[NUM_BINS] = {0};
    int lcl_cnt[NUM_BINS] = {0};
    double bin_width = (MAX_VAL - MIN_VAL) / (double)NUM_BINS;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (rank == 0) {
        // Generate random data
        for (i = 0; i < N; i++) {
            data[i] = (double)rand() / (double)RAND_MAX;
        }

        start_time = MPI_Wtime();
    }

    // Scatter the data to the slaves
    int chunk_size = N / num_procs;
    double local_data[chunk_size];

    MPI_Scatter(data, chunk_size, MPI_DOUBLE, local_data, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Count the number of measurements in each bin in the local data
    for (i = 0; i < chunk_size; i++) {
        int bin = (int)((local_data[i] - MIN_VAL) / bin_width);
        lcl_cnt[bin]++;
    }

    // Reduce the counts to the master
    MPI_Reduce(lcl_cnt, counts, NUM_BINS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Master process prints the histogram
        end_time = MPI_Wtime();

        printf("Histogram:\n");
        for (i = 0; i < NUM_BINS; i++) {
            double bin_start = i * bin_width + MIN_VAL;
            double bin_end = (i + 1) * bin_width + MIN_VAL;
            printf("[%f, %f]: %d\n", bin_start, bin_end, counts[i]);
        }

        printf("Elapsed time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
