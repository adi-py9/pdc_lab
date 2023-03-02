#include <stdio.h>
#include <omp.h>

int main() {
    int num_procs, num_threads, thread_num, is_dynamic, is_nested;

    // get number of processors
    num_procs = omp_get_num_procs();
    printf("Number of processors: %d\n", num_procs);

    // set number of threads and get actual number of threads
    omp_set_num_threads(4);
    num_threads = omp_get_num_threads();
    printf("Number of threads: %d\n", num_threads);

    // check if in parallel region and get thread number
    #pragma omp parallel private(thread_num)
    {
        thread_num = omp_get_thread_num();
        printf("Thread number: %d\n", thread_num);
        if (omp_in_parallel()) {
            printf("In parallel region\n");
        } else {
            printf("Not in parallel region\n");
        }
    }

    // check if dynamic adjustment of threads is allowed
    is_dynamic = omp_get_dynamic();
    printf("Dynamic adjustment of threads: %d\n", is_dynamic);

    // check if nested parallelism is enabled
    is_nested = omp_get_nested();
    printf("Nested parallelism enabled: %d\n", is_nested);

    return 0;
}
