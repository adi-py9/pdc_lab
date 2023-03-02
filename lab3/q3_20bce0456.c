#include <stdio.h>
#include <omp.h>

int main() {
    int num_procs, num_threads, thread_num, is_dynamic, is_nested;    
    
    num_procs = omp_get_num_procs();// get number of processors
    printf("Number of processors: %d\n", num_procs);
    
    omp_set_num_threads(4);// set number of threads
    num_threads = omp_get_num_threads();//get actual number of threads
    
    printf("Number of threads: %d\n", num_threads);

    
    #pragma omp parallel private(thread_num)
    {
        thread_num = omp_get_thread_num();//get thread number
        printf("Thread number: %d\n", thread_num);
        
        if (omp_in_parallel()) //check in parallel region 
        {
            printf("\nIn parallel region\n");
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
