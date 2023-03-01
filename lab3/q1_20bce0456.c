#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int a[N][N], b[N][N], c[N][N];
    int i, j, k;

    // initialize matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
            c[i][j] = 0;
        }
    }

    // perform matrix multiplication using OpenMP parallelization
    #pragma omp parallel for shared(a,b,c) private(i,j,k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // print result matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}