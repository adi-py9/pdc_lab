#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 10000
#define NUM_BINS 100

int main(int argc, char** argv) {
    int rank, size;
    int i, j;
    float data[ARRAY_SIZE];
    int counts[NUM_BINS];
    float min_val, max_val;
    float bin_width;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Generate data
    for (i = 0; i < ARRAY_SIZE; i++) {
        data[i] = (float) rand() / RAND_MAX;
    }

    // Partition the data
    int local_size = ARRAY_SIZE / size;
    float* local_data = malloc(local_size * sizeof(float));
    MPI_Scatter(data, local_size, MPI_FLOAT, local_data, local_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Determine the range of the data
    MPI_Allreduce(&local_data[0], &min_val, 1, MPI_FLOAT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&local_data[0], &max_val, 1, MPI_FLOAT, MPI_MAX, MPI_COMM_WORLD);

    // Determine the bin width
    bin_width = (max_val - min_val) / NUM_BINS;

    // Compute the local histogram
    for (i = 0; i < NUM_BINS; i++) {
        counts[i] = 0;
    }
    for (i = 0; i < local_size; i++) {
        int bin = (local_data[i] - min_val) / bin_width;
        if (bin < 0) {
            bin = 0;
        } else if (bin >= NUM_BINS) {
            bin = NUM_BINS - 1;
        }
        counts[bin]++;
    }

    // Combine the histograms
    int* all_counts = NULL;
    if (rank == 0) {
        all_counts = malloc(NUM_BINS * size * sizeof(int));
    }
    MPI_Gather(counts, NUM_BINS, MPI_INT, all_counts, NUM_BINS, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the final histogram
    if (rank == 0) {
        for (i = 0; i < NUM_BINS; i++) {
            int sum = 0;
            for (j = 0; j < size; j++) {
                sum += all_counts[i + j * NUM_BINS];
            }
            printf("%f - %f: %d\n", min_val + i * bin_width, min_val + (i+1) * bin_width, sum);
        }
        free(all_counts);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}
