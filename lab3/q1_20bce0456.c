#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100 // initialized the size of matrices

int main() {
    double *A, *B, *C;
    int i, j, k;

    // Allocate memory for matrices A, B, and C
    A = (double *) malloc(N * N * sizeof(double));
    B = (double *) malloc(N * N * sizeof(double));
    C = (double *) malloc(N * N * sizeof(double));

    // Initialize matrices A and B with random values
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i * N + j] = (double) rand() / RAND_MAX;
            B[i * N + j] = (double) rand() / RAND_MAX;
        }
    }

    // Parallelize the matrix multiplication using OpenMP
    #pragma omp parallel for shared(A,B,C) private(i,j,k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] = 0.0;
            for (k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    // Print the result
    printf("Result matrix C (row(s)):\n");
for (j = 0; j < 10; j++) {
    printf("%0.2f\n", C[j]);
}
printf("\n");
printf("Result matrix C (columns(s)):\n");
for (i = 0; i < 10; i++) {
    printf("%0.2f\n", C[i * N]);
}

    // Free memory
    free(A);
    free(B);
    free(C);

    return 0;
}
