#include <stdio.h>
#include <omp.h>

#define SIZE 5

int main() {
    int arr1[SIZE] = {4, 5, 6, 11, 13};
    int arr2[SIZE] = {17, 2, 3, 19, 1};
    int result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < SIZE; i++) {
        result += arr1[i] * arr2[i];
    }

    printf("Dot product: %d\n", result);

    return 0;
}
