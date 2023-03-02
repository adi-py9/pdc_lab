#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 100
#define M 100
#define P 100

int main() {
    int a[N][M], b[M][N], c[N][P];
    int i, j, k;

    // initialize matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
            c[i][j] = 0;
        }
    }
    // //test : printing a matrix
    //  for (i = 0; i < N; i++) {
    //     for (j = 0; j < M; j++) {
    //         printf("%d ", a[i][j]);
    //     }
    //     printf("\n");
    // }

    // //test : printing b matrix
    //  for (i = 0; i < N; i++) {
    //     for (j = 0; j < M; j++) {
    //         printf("%d ", b[i][j]);
    //     }
    //     printf("\n");
    // }


    // perform matrix multiplication using OpenMP parallelization
    #pragma omp parallel for shared(a,b,c) private(i,j,k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < P; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    //print result matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}