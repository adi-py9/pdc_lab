#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>
int main(int argc, char **argv) {
    int rank, size;
    long long int number_of_tosses, toss, number_in_circle = 0;
    double x, y, distance_squared, pi_estimate, start_time, end_time, total_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            printf("Usage: mpiexec -n <number_of_processes> ./pi_mpi <number_of_tosses>\n");
        }
        MPI_Finalize();
        exit(1);
    }

    number_of_tosses = atoll(argv[1]);

    start_time = MPI_Wtime();

    srand((unsigned int)time(NULL) + rank);

    for (toss = 0; toss < number_of_tosses; toss++) {
        x = ((double)rand() / (double)RAND_MAX) * 2 - 1;
        y = ((double)rand() / (double)RAND_MAX) * 2 - 1;
        distance_squared = x * x + y * y;
        if (distance_squared <= 1) {
            number_in_circle++;
        }
    }

    MPI_Reduce(&number_in_circle, &number_in_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi_estimate = 4 * number_in_circle / ((double)number_of_tosses * size);
        end_time = MPI_Wtime();
        total_time = end_time - start_time;
        printf("Estimate of pi: %f\n", pi_estimate);
        printf("Time taken: %f seconds\n", total_time);
    }

    MPI_Finalize();
    return 0;
}
