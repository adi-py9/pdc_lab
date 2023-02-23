#include <stdio.h>
#include <omp.h>

#define SIZE 5

int main() 
{
    int arr1[SIZE] = {4, 5, 6, 12, 13};
    int arr2[SIZE] = {8, 1, 2, 19, 21};
    int arr3[SIZE];

    #pragma omp parallel num_threads(5)
    {
        int id = omp_get_thread_num();
        arr3[id] = arr1[id] + arr1[id];
        printf("Thread %d: arr3[%d] = %d\n", id, id, arr3[id]);
    }

    return 0;
}
