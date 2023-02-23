#include <omp.h>
#include <stdio.h>
#define N 1000

int main() {
int i, sum = 0;
#pragma omp parallel for reduction(+:sum)
for (i = 0; i < N; i++) {
sum += i * i;
int id = omp_get_thread_num();
printf("Thread ID: %d, Sum = %d\n", id, sum);
}
printf("Final sum of dot product of first %d numbers = %d\n", N, sum);
return 0;
}