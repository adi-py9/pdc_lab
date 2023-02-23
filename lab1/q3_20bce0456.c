#include <stdio.h>
#include <omp.h>

#define SIZE 100
#define CHUNK_SIZE 10

int main() {
    int arr1[SIZE];

    for (int i = 0; i < SIZE; i++) {
        arr1[i] = i;
    }

    #pragma omp parallel for schedule(dynamic, CHUNK_SIZE)
    for (int i = 0; i < SIZE; i++) {
        printf("Thread %d: arr1[%d] = %d\n", omp_get_thread_num(), i, arr1[i]);
    }

    return 0;
}
