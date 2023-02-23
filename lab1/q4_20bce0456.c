#include <stdio.h>
#include <omp.h>

#define SIZE 10

int main() {
    int arr1[SIZE] = {10, 2, 17, 19, 3};
    int sum = 0, subtraction=0;
    float product = 0.0,division=0.0;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < SIZE; i++) {
                sum += arr1[i];
            }
            printf("Thread %d: Sum = %d\n", omp_get_thread_num(), sum);
        }

        #pragma omp section
        {
            for (int i = 0; i < SIZE; i++) {
                product *= arr1[i];
            }
            printf("Thread %d: Product = %d\n", omp_get_thread_num(), product);
        }
        #pragma omp section
        {
            for (int i = 0; i < SIZE; i++) {
                subtraction -= arr1[i];
            }
            printf("Thread %d: Subtraction = %d\n", omp_get_thread_num(), subtraction);
        }
        #pragma omp section
        {
            for (int i = 0; i < SIZE; i++) {
                if (arr1[i]!=0)
                division /= arr1[i];
            }
            printf("Thread %d: Division = %d\n", omp_get_thread_num(), division);
        }
    }
    return 0;
}
